'''
Account Module

Description:
  Contains the different account types that can be used by the agents

Author:
  Elvis Payano
'''
class Account():
  '''
  An account model used to simulate a non margined brokerage account as trades are made
  '''

  def __init__(self, init_bal = 0):
    '''
    Initialize an account with the provided initial balance

    Keyword Arguments:
      init_bal -- Initial balance (default 0.0)
    '''
    self._balance  = init_bal
    self._profit   = 0.0
    self._holdings = 0
    self._transactions = list()

  def purchase(self, price, quantity = 1):
    '''
    Puchase stocks

    Keyword Arguments:
      price     -- Purchase price
      quantity  -- Purchase quantity (default 1)
    '''
    if (price * quantity) > self._balance:
      return False

    self._balance  -= price * quantity
    self._holdings += quantity

    self._transactions.append(price)
    return True

  def sell(self, price, quantity = 1):
    '''
    Sell stocks

    Keyword Arguments:
      price     -- Sell price
      quantity  -- Sell quantity (default 1)
    '''
    if self._holdings < quantity:
      return False

    self._balance  += price * quantity
    self._holdings -= quantity

    self._profit += price - self._transactions[0]
    self._transactions.pop(0)
    return True

  def get_holdings(self):
    '''
    Current number of holdings
    '''
    return self._holdings

  def get_balance(self):
    '''
    Current balance
    '''
    return self._balance

  def get_pnl(self):
    '''
    Current profit/loss (PnL)
    '''
    return self._profit
