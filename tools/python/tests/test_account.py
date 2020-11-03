# Algo Trainer Account (Tests)
#
# Run tests on the Algorithm Trader Training Account module
#
# Author: Elvis Payano

# Import Standard Modules
from unittest import TestCase, main
from random   import random, randint

# Import Custom Modules
from algo_trainer.account import Account

class TestAccount(TestCase):
  def setUp(self):
    self.initBal = random() * 1e3
    self.account = Account(initial_balance=self.initBal)

  def test_initialization(self):
    acc = Account()
    self.assertEqual(acc.getBalance() , 0)
    self.assertEqual(acc.getHoldings(), 0)
    self.assertEqual(acc.getPnL()     , 0)

    self.assertEqual(self.account.getBalance() , self.initBal)
    self.assertEqual(self.account.getHoldings(), 0)
    self.assertEqual(self.account.getPnL()     , 0)

  def test_good_trades(self):
    totalShares = randint(5,10)
    quantity = randint(1, totalShares)
    marketPrice = self.initBal / (totalShares + 1)
    self.assertTrue(self.account.purchase(marketPrice, quantity))
    self.assertEqual(self.account.getHoldings(),  quantity)
    self.assertAlmostEqual(self.account.getBalance(),   self.initBal - (marketPrice*quantity))
    self.assertAlmostEqual(self.account.getPnL(),       0)

    priceChange = random()
    priceDiff = marketPrice * priceChange
    marketPrice *= (1 + priceChange)
    self.assertTrue(self.account.sell(marketPrice, quantity))
    self.assertEqual(self.account.getHoldings(),  0)
    self.assertAlmostEqual(self.account.getBalance(),   self.initBal + priceDiff*quantity)
    self.assertAlmostEqual(self.account.getPnL(),       priceDiff*quantity)

  def test_bad_trades(self):
    totalShares = randint(5,10)
    quantity = randint(1, totalShares)
    marketPrice = self.initBal * (totalShares + 1)
    self.assertFalse(self.account.purchase(marketPrice, quantity))
    self.assertEqual(self.account.getHoldings(),  0)
    self.assertEqual(self.account.getBalance(),   self.initBal)

    self.assertFalse(self.account.sell(marketPrice, quantity))
    self.assertEqual(self.account.getHoldings(),  0)
    self.assertEqual(self.account.getBalance(),   self.initBal)

if __name__ == '__main__':
  main()