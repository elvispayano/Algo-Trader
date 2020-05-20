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

def yfextractelement(history,content):
  element = list()

  if "Datetime" in content:
    temp = history.axes[0]
    data = list()
    for i in range(0,len(temp)):
      data.append(str(temp[i]).replace("-04:00",""))
  else:
    data = history[content]

  for entry in data:
    element.append(entry)

  return element

def hist2cell(history):
  # Validate input types
  if type(history) is not type(DataFrame()):
    raise(TypeError)

  # Capture entry data
  elements = list()
  for title in history.axes[1]:
    elements.append(title)

  Cell = list()

  Date      = yfextractelement(history,"Datetime")
  Open      = yfextractelement(history,"Open")
  High      = yfextractelement(history,"High")
  Low       = yfextractelement(history,"Low")
  Close     = yfextractelement(history,"Close")
  Volume    = yfextractelement(history,"Volume")
  
  for i in range(0,len(Open)):
    Group = [Date[i], Open[i], High[i], Low[i], Close[i], Volume[i]]
    Cell.append(Group)

  return Cell

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
def fetch(tick, fp='max', fi='1d'):
  # Validate input types
  if (type(tick) is not type(str())) or \
     (type(fp) is not type(str())) or \
     (type(fi) is not type(str())):
    raise(TypeError)

  # Request and return ticker historical data
  return yfinance.Ticker(tick).history(period=fp, interval=fi)
