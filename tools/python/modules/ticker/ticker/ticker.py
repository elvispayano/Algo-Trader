# ticker
# Yahoo Finance interface file that provides up to data information for
# tickers listed on the stock exchange. Data is all adjusted into current
# currency standards.
#
# Author: Elvis Payano

# Imports
import yfinance as yf

# Fetch
# Returns a structured dictionary element that contains requested
# historical data
#
# Input:
#   Tick = String element of a ticker symbol
#
# Output:
#   HistData = Dictionary with requested fields
def fetch(tick, fp='max', fi='1d'):
  if type(tick) is not type(str()):
    raise(TypeError)

  Ticker = yf.Ticker(tick)
  hist = Ticker.history(period=fp, interval=fi)
  return yfhist2cell(hist)

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

def yfhist2cell(history):
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