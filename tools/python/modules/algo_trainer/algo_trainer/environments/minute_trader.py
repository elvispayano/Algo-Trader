# Minute Trade Environment
#
# An environment model that simulates an environment in which only
# minute interval trades are allowed.
#
# Author: Elvis Payano

import numpy as np
from pandas import read_table
import tensorflow as tf

# Python Imports
from tf_agents.environments import py_environment
from tf_agents.environments import utils
from tf_agents.trajectories import time_step as ts
from tf_agents.specs        import array_spec

from algo_trainer.account   import Account

tf.compat.v1.enable_v2_behavior()

class MinuteTraderEnvironment(py_environment.PyEnvironment):
  def __init__(self, ticker='MSFT'):
    self._action_spec = array_spec.BoundedArraySpec(shape=(), dtype=np.int32,
      minimum=0, maximum=2, name='Trade Action')

    self._observation_spec = array_spec.BoundedArraySpec(
      shape=(4,), dtype=np.float32, name='Market/Account Data')

    

    self._reset()

    stockData = read_table('{0}.txt'.format(ticker),delimiter=',')
    self._Open  = stockData['Open']
    self._High  = stockData['High']
    self._Low   = stockData['Low']
    self._Close = stockData['Close']
    
    self._endIndex = len(stockData) - 1

  def action_spec(self):
    return self._action_spec

  def observation_spec(self):
    return self._observation_spec

  # Reset the environment to a default state for each training episode
  def _reset(self):
    self._account = Account()
    self._index = 0
    self._state = [
      self._account.getBalance(),
      0,
      0,
      self._account.getBalance()
      ]
    self._episode_ended = False
    
    return ts.restart(np.array(self._state, dtype=np.float32))

  # Step episode through environment
  def _step(self, action):
    if self._episode_ended:
      return self._reset()

    self._index += 1
    index = self._index
    goodAction = False
    stepReward = 0

    marketPrice = (self._High[index] + self._Low[index] + self._Open[index])/3

    if action == 0:   # Buy
      goodAction = self._account.purchase(marketPrice)
    elif action == 1: # Hold
      goodAction = self._account.getHoldings() > 0
    elif action == 2: # Sell
      goodAction = self._account.sell(marketPrice)

    if goodAction:
      stepReward = 1/6000
    else:
      stepReward = -1/6000

    outputState = [
      self._account.getBalance(),
      self._account.getHoldings(),
      self._account.getPnL(),
      self._account.getBalance() + self._account.getHoldings() * marketPrice
    ]

    if index == self._endIndex:
      self._episode_ended = True
      #print("Episode Profit:", self._account.getPnL())
      return ts.termination(np.array(outputState, dtype=np.float32), reward=stepReward)

    return ts.transition(np.array(outputState, dtype=np.float32), reward=stepReward, discount=1.0)

if __name__ == '__main__':
  env = MinuteTraderEnvironment()
  utils.validate_py_environment(env, episodes=5)
