# Account Class
#
# An account model used to simulate updates to the brokerage account
# as trades are made.
#
# Author: Elvis Payano

class Account():
  def __init__(self, initial_balance = 0):
    self._balance  = initial_balance
    self._profit   = 0.0
    self._holdings = 0
    
    self._transactions = list()

  def purchase(self, price, quantity = 1):
    if (price * quantity) > self._balance:
      return False
      
    self._balance  -= price * quantity
    self._holdings += quantity

    self._transactions.append(price)
    return True

  def sell(self, price, quantity = 1):
    if self._holdings < quantity:
      return False
    
    self._balance  += price * quantity
    self._holdings -= quantity

    self._profit += price - self._transactions[0]
    self._transactions.pop(0)
    return True

  def getHoldings(self):
    return self._holdings

  def getBalance(self):
    return self._balance

  def getPnL(self):
    return self._profit

