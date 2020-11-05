'''
Minute Trader Module

Description:
  Contains the environment and functionality to support a minute interval simulated
  trading environment

Author:
  Elvis Payano
'''

# Tensorflow Imports
import tensorflow           as tf
from tf_agents.environments import py_environment
from tf_agents.trajectories import time_step as ts
from tf_agents.specs        import array_spec

# Algo Trainer Imports
from algo_trainer.account   import Account

# Support Imports
import numpy                as np

tf.compat.v1.enable_v2_behavior()

class MinuteTraderEnvironment(py_environment.PyEnvironment):
  '''
  A simulated trading environment in which only minute interval trades are allowed.
  '''
  # pylint: disable=too-many-instance-attributes

  def __init__(self, stock_data):
    '''
    Initialize the minute trader environment

    Keywork Arguments:
      stock_data -- Training dataset
    '''
    super().__init__()
    self._action_spec = array_spec.BoundedArraySpec(shape=(), dtype=np.int32,
      minimum=0, maximum=2, name='Trade Action')

    self._observation_spec = array_spec.BoundedArraySpec(
      shape=(4,), dtype=np.float32, name='Market/Account Data')

    self._reset()
    self._open  = stock_data['Open']
    self._high  = stock_data['High']
    self._low   = stock_data['Low']
    self._close = stock_data['Close']

    self._end_index = len(stock_data) - 1
    self._episode_ended = False
    self._step_output = None

  def action_spec(self):
    '''
    Environment action spec
    '''
    return self._action_spec

  def observation_spec(self):
    '''
    Environment observation spec
    '''
    return self._observation_spec

  def _reset(self):
    '''
    Reset the environment to a default state for each training episode
    '''
    self._account = Account()
    self._index = 0
    self._state = [
      self._account.get_balance(),
      0,
      0,
      self._account.get_balance()
      ]
    self._episode_ended = False

    self._step_output = ts.restart(np.array(self._state, dtype=np.float32))
    return self._step_output

  def _step(self, action):
    '''
    Step episode through environment

    Keyword Arguments:
      action -- Network selected action
    '''
    if self._episode_ended:
      return self._reset()

    self._index += 1
    index = self._index
    good_action = False
    step_reward = 0

    market_price = (self._high[index] + self._low[index] + self._open[index])/3

    if action == 0:   # Buy
      good_action = self._account.purchase(market_price)
    elif action == 1: # Hold
      good_action = self._account.get_holdings() > 0
    elif action == 2: # Sell
      good_action = self._account.sell(market_price)

    if good_action:
      step_reward = 1/self._end_index
    else:
      step_reward = -1/self._end_index

    output_state = [
      self._account.get_balance(),
      self._account.get_holdings(),
      self._account.get_pnl(),
      self._account.get_balance() + self._account.get_holdings() * market_price
    ]

    if index == self._end_index:
      self._episode_ended = True
      #print("Episode Profit:", self._account.get_pnl())
      self._step_output = ts.termination(
                            np.array(output_state, dtype=np.float32),
                            reward=step_reward)
    else:
      self._step_output = ts.transition(
                            np.array(output_state, dtype=np.float32),
                            reward=step_reward,
                            discount=1.0)

    return self._step_output

  def get_info(self):
    '''
    Get the environment info returned on the last step
    '''
    return self._step_output

  def get_state(self):
    '''
    Return the current state of the environment
    '''
    return None

  def set_state(self, state):
    '''
    Set the current state of the environment
    '''
    return None
