'''
Interface Module

Description:
  Yahoo Finance interface file that provides up to data information for
  tickers listed on the stock exchange. Data is all adjusted into current
  currency standards.

Author:
  Elvis Payano
'''

# Python Imports
import yfinance
from pandas.core.frame import DataFrame

def dataframe2cell(history):
  '''
  Convert pandas DataFrame type into a 2D element array where the first
  colum represents the datetime

  Keyword Arguments:
    history -- Ticker data set
  '''

  # Validate input types
  if not isinstance(history, DataFrame):
    raise TypeError

  # Capture entry data
  dates = list(history.index)
  columns = list(history.columns)

  # Gather data and iterate through each element to enter into
  # a growing 2D list
  cell_data = list()
  count = 0
  for day in dates:
    data = list()
    data.append(str(day))
    for col in columns:
      data_value = float(history[str(col)][count])
      if data_value.is_integer():
        data.append(int(data_value))
      else:
        data.append(data_value)
    cell_data.append(data)
    count = count + 1

  return cell_data

def fetch(tick, per='max', inter='1d'):
  '''
  Returns a Pandas Data structure that contains the requested
  historical data

  Keyword Arguments:
    tick  -- Ticker Symbol
    per   -- Fetch Period
    inter -- Fetch Interval
  '''
  # Validate input types
  if not isinstance(tick, str) or not isinstance(per, str) or not isinstance(inter, str):
    raise TypeError

  # Request and return ticker historical data
  return yfinance.Ticker(tick).history(period=per, interval=inter)
