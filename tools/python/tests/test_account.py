'''
Test Account Module

Description:
  Tests the implementation of the account module

Author:
  Elvis Payano
'''

# Import Standard Modules
from unittest import TestCase, main
from random   import random, randint

# Import Custom Modules
from algo_trainer.account import Account

class TestAccount(TestCase):
  '''
  Test the Account class in the Account module
  '''
  def setUp(self):
    '''
    Setup the account class used for each test
    '''
    self.init_bal = random() * 1e3
    self.account = Account(init_bal=self.init_bal)

  def test_initialization(self):
    '''
    Test initialization of Account class
    '''
    acc = Account()
    self.assertEqual(acc.get_balance() , 0)
    self.assertEqual(acc.get_holdings(), 0)
    self.assertEqual(acc.get_pnl()     , 0)

    self.assertEqual(self.account.get_balance() , self.init_bal)
    self.assertEqual(self.account.get_holdings(), 0)
    self.assertEqual(self.account.get_pnl()     , 0)

  def test_good_trades(self):
    '''
    Test functionality of successful trades
    '''
    total_shares = randint(5,10)
    quantity = randint(1, total_shares)
    market_price = self.init_bal / (total_shares + 1)
    self.assertTrue(self.account.purchase(market_price, quantity))
    self.assertEqual(self.account.get_holdings(),  quantity)
    self.assertAlmostEqual(self.account.get_balance(),   self.init_bal - (market_price*quantity))
    self.assertAlmostEqual(self.account.get_pnl(),       0)

    price_change = random()
    price_diff = market_price * price_change
    market_price *= (1 + price_change)
    self.assertTrue(self.account.sell(market_price, quantity))
    self.assertEqual(self.account.get_holdings(),  0)
    self.assertAlmostEqual(self.account.get_balance(),   self.init_bal + price_diff*quantity)
    self.assertAlmostEqual(self.account.get_pnl(),       price_diff*quantity)

  def test_bad_trades(self):
    '''
    Test functionality of unsuccessful trades
    '''
    total_shares = randint(5,10)
    quantity = randint(1, total_shares)
    market_price = self.init_bal * (total_shares + 1)
    self.assertFalse(self.account.purchase(market_price, quantity))
    self.assertEqual(self.account.get_holdings(),  0)
    self.assertEqual(self.account.get_balance(),   self.init_bal)

    self.assertFalse(self.account.sell(market_price, quantity))
    self.assertEqual(self.account.get_holdings(),  0)
    self.assertEqual(self.account.get_balance(),   self.init_bal)

if __name__ == '__main__':
  main()
