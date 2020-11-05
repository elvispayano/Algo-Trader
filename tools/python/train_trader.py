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
  stockData = read_table('{0}.txt'.format(ticker),delimiter=',')
  trainEnv = tf_py_environment.TFPyEnvironment(MinuteTraderEnvironment('MSFT'))

  # Create Actor Network
  actorNetwork = networks.q_network.QNetwork(
    trainEnv.observation_spec(),
    trainEnv.action_spec(),
    fc_layer_params=fc_layer_params
  )
  #actorNetwork = networks.actor_distribution_network.ActorDistributionNetwork(
  #  input_tensor_spec=trainEnv.observation_spec(),
  #  output_tensor_spec=trainEnv.action_spec()
  #  )

  # Agent Options  
  agentOptimizer = tf.compat.v1.train.AdamOptimizer(learning_rate=learning_rate)
  trainStepCounter = tf.compat.v2.Variable(0)

  # Create Agent
  tfAgent = agents.DqnAgent(
    trainEnv.time_step_spec(),
    trainEnv.action_spec(),
    q_network=actorNetwork,
    optimizer=agentOptimizer,
    td_errors_loss_fn=common.element_wise_squared_loss,
    train_step_counter=trainStepCounter
  )
  #tfAgent = agents.ReinforceAgent(
  #  actor_network=actorNetwork,
  #  optimizer=agentOptimizer,
  #  train_step_counter=trainStepCounter,
  #  action_spec=trainEnv.action_spec(),
  #  time_step_spec=trainEnv.time_step_spec()
  #  )
  tfAgent.initialize()

  avg_reward = get_average_reward(trainEnv, tfAgent.policy, 2)
  print("Average Reward:", avg_reward)

  ## Capture State Action Pairs
  # A repository of trajectories used to train agent. The larger the buffer, the more variety
  # is available for the agent to train on
  replayBuffer = tf_uniform_replay_buffer.TFUniformReplayBuffer(
    data_spec=tfAgent.collect_data_spec,
    batch_size=trainEnv.batch_size,
    max_length=int(1e6))

  replayBufferObserver = replayBuffer.add_batch

  ## Driver and Observer
  # Driver is responsible collecting trajectories from the environment
  trainMetrics = [
    tf_metrics.AverageReturnMetric(),
    tf_metrics.AverageEpisodeLengthMetric()
  ]

  collectDriver = dynamic_step_driver.DynamicStepDriver(
    trainEnv,
    tfAgent.collect_policy,
    observers=[replayBufferObserver] + trainMetrics,
    num_steps=5048
  )

  ## Initialize Training Environment
  # Utilizing a random policy
  initialCollectPolicy = random_tf_policy.RandomTFPolicy(trainEnv.time_step_spec(), trainEnv.action_spec())

  initDriver = dynamic_step_driver.DynamicStepDriver(
    trainEnv,
    initialCollectPolicy,
    observers=[replayBuffer.add_batch],
    num_steps=int(2e4)
  )

  finalTimeStep, finalPolicyState = initDriver.run()

  
  dataset = replayBuffer.as_dataset(sample_batch_size=64, num_steps=2, num_parallel_calls=3).prefetch(3)

  tfAgent = train_agent(int(1.5e6), tfAgent, trainEnv, collectDriver, trainMetrics, dataset)