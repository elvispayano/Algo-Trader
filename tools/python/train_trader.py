# Python Imports
import tensorflow as tf
from tf_agents.environments   import tf_py_environment
from tf_agents                import networks
from tf_agents                import agents
from tf_agents.replay_buffers import tf_uniform_replay_buffer
from tf_agents.drivers        import dynamic_step_driver
from tf_agents.metrics        import tf_metrics
from tf_agents.policies       import random_tf_policy

# TBD
from tf_agents              import trajectories
from tf_agents.utils import common

import matplotlib.pyplot as plt

# Local Imports
from algo_trainer.environments import minute_trader
from pandas import read_table

# Global Variables
num_iterations = 100 #10000  # @param

initial_collect_steps       = 1000    # @param
collect_steps_per_iteration = 1       # @param
replay_buffer_capacity      = 100000  # @param

fc_layer_params = (100,)

batch_size    = 128   # @param
learning_rate = 1e-5  # @param
log_interval  = 200   # @param

num_eval_episodes = 2     # @param
eval_interval     = 1000  # @param

def get_average_reward(environment, policy, episodes=10):
  total_reward = 0.0

  for _ in range(episodes):
    time_step = environment.reset()
    episode_reward = 0.0

    while not time_step.is_last():
      action_step = policy.action(time_step)
      time_step = environment.step(action_step.action)
      episode_reward += time_step.reward
  
    total_reward += episode_reward
    avg_reward = total_reward / episodes

  return avg_reward.numpy()[0]

def train_agent(n_iterations, agent, train_env, collect_driver, train_metrics, dataset):
  print("Training Agent")
  time_step = None
  all_train_loss = list()
  all_metrics = list()
  policy_state = agent.collect_policy.get_initial_state(train_env.batch_size)
  iterator = iter(dataset)

  for iteration in range(n_iterations):
    current_metrics = []

    time_step, policy_state = collect_driver.run(time_step, policy_state)
    trajectories, buffer_info = next(iterator)

    train_loss = agent.train(trajectories)
    all_train_loss.append(train_loss.loss.numpy())

    for i in range(len(train_metrics)):
      current_metrics.append(train_metrics[i].result().numpy())

    all_metrics.append(current_metrics)

    if iteration % 10 == 0:
      print("\nIteration: {}, loss:{:.2f}".format(iteration, train_loss.loss.numpy()))

      for i in range(len(train_metrics)):
        print('{}: {}'.format(train_metrics[i].name, train_metrics[i].result().numpy()))

  return agent


if __name__ == '__main__':
  # Generate Training Environment
  stock_data = read_table('{0}.txt'.format('MSFT'),delimiter=',')
  train_env = tf_py_environment.TFPyEnvironment(MinuteTraderEnvironment(stock_data))

  # Create Actor Network
  actor_network = networks.q_network.QNetwork(
    train_env.observation_spec(),
    train_env.action_spec(),
    fc_layer_params=fc_layer_params
  )
  #actor_network = networks.actor_distribution_network.ActorDistributionNetwork(
  #  input_tensor_spec=train_env.observation_spec(),
  #  output_tensor_spec=train_env.action_spec()
  #  )

  # Agent Options
  agentOptimizer = tf.compat.v1.train.AdamOptimizer(learning_rate=learning_rate)
  trainStepCounter = tf.compat.v2.Variable(0)

  # Create Agent
  tf_agent = agents.DqnAgent(
    train_env.time_step_spec(),
    train_env.action_spec(),
    q_network=actor_network,
    optimizer=agentOptimizer,
    td_errors_loss_fn=common.element_wise_squared_loss,
    train_step_counter=trainStepCounter
  )
  #tf_agent = agents.ReinforceAgent(
  #  actor_network=actor_network,
  #  optimizer=agentOptimizer,
  #  train_step_counter=trainStepCounter,
  #  action_spec=train_env.action_spec(),
  #  time_step_spec=train_env.time_step_spec()
  #  )
  tf_agent.initialize()

  avg_reward = get_average_reward(train_env, tf_agent.policy, 2)
  print("Average Reward:", avg_reward)

  ## Capture State Action Pairs
  # A repository of trajectories used to train agent. The larger the buffer, the more variety
  # is available for the agent to train on
  replay_buffer = tf_uniform_replay_buffer.TFUniformreplay_buffer(
    data_spec=tf_agent.collect_data_spec,
    batch_size=train_env.batch_size,
    max_length=int(1e6))

  replay_bufferObserver = replay_buffer.add_batch

  ## Driver and Observer
  # Driver is responsible collecting trajectories from the environment
  train_metrics = [
    tf_metrics.AverageReturnMetric(),
    tf_metrics.AverageEpisodeLengthMetric()
  ]

  collect_driver = dynamic_step_driver.DynamicStepDriver(
    train_env,
    tf_agent.collect_policy,
    observers=[replay_bufferObserver] + train_metrics,
    num_steps=5048
  )

  ## Initialize Training Environment
  # Utilizing a random policy
  initial_collect_policy = random_tf_policy.RandomTFPolicy(train_env.time_step_spec(), train_env.action_spec())

  init_driver = dynamic_step_driver.DynamicStepDriver(
    train_env,
    initial_collect_policy,
    observers=[replay_buffer.add_batch],
    num_steps=int(2e4)
  )

  finalTimeStep, finalPolicyState = init_driver.run()

  dataset = replay_buffer.as_dataset(sample_batch_size=64, num_steps=2, num_parallel_calls=3).prefetch(3)

  tf_agent = train_agent(int(1.5e6), tf_agent, train_env, collect_driver, train_metrics, dataset)
