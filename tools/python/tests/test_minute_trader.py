'''
Test Minute Trader Module

Description:
  Tests the implementation of the environment module

Author:
  Elvis Payano
'''

# Import Standard Modules
from unittest import TestCase, main
from random   import sample

# Import Custom Modules
from algo_trainer.environments import minute_trader

class TestMinuteTraderEnvironment(TestCase):
  '''
  Test the Minute Trader Environment class in the environment module
  '''

  def setUp(self):
    '''
    Setup the Minute Trader Environment class used for each test
    '''
    elements = ['High', 'Low', 'Open', 'Close']
    data = dict()

    for element in elements:
      data[element] = sample(range(50, 100), 100)
    self.env = minute_trader.MinuteTraderEnvironment(data)

if __name__ == '__main__':
  main()
