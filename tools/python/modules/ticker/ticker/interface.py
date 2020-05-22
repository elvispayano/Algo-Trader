# Interface
#
# Yahoo Finance interface file that provides up to data information for
# tickers listed on the stock exchange. Data is all adjusted into current
# currency standards.
#
# Author: Elvis Payano

# Imports
import yfinance
from pandas.core.frame import DataFrame

# DataFrame2Cell
#
# Convert pandas DataFrame type into a 2D element array where the first
# column represents the datetime.
#
# Input:
#   History = Pandas Data Type
#
# Output
#   CellData = 2D list of "History" contents
#
def dataframe2cell(history):
  # Validate input types
  if not isinstance(history, DataFrame):
    raise TypeError

  # Capture entry data
  dates = list(history.index)
  columns = list(history.columns)

  # Gather data and iterate through each element to enter into
  # a growing 2D list
  cellData = list()
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
    cellData.append(data)
    count = count + 1

  return cellData

# Fetch
#
# Returns a Pandas Data structure that contains the requested
# historical data
#
# Input:
#   Tick = String element of a ticker symbol
#
# Output:
#   HistData = Pandas Data Type
#
def fetch(tick, fp='max', fi='1d'):
  # Validate input types
  if not isinstance(tick, str) or not isinstance(fp, str) or not isinstance(fi, str):
    raise TypeError

  # Request and return ticker historical data
  return yfinance.Ticker(tick).history(period=fp, interval=fi)
