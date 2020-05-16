#----------------------------------------------------------------------
# Imports
#----------------------------------------------------------------------
import yfinance as yf

#----------------------------------------------------------------------
# Support Functions
#----------------------------------------------------------------------
# Fetch Ticker Data
def FetchHistory(tick):
  Ticker = yf.Ticker(tick)
  hist = Ticker.history(period='max', interval='1d')
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