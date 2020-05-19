# Import Standard Modules
from unittest import TestCase, main, mock
from pandas.core.frame import DataFrame

# Import Custom Modules
from ticker import interface

class TestTickerInterface(TestCase):

    def setUp(self):
        Col = {"Date":["2020-05-18"]}
        data = {
            "Open" : [185.75],
            "High" : [186.20],
            "Low" : [183.98],
            "Close": [184.91],
            "Volume": [34415475],
        }
        self.mocked_output = DataFrame(data=data,index=Col)

    def tearDown(self):
        pass
    
    def test_fetch(self):
        with self.assertRaises(TypeError):
            interface.fetch(1)
            interface.fetch("XYZ", fp=[1,2,3])
            interface.fetch("XYZ", fi=[1,2,3])

        with mock.patch('ticker.interface.yfinance.ticker.TickerBase.history') as mocked_history:
            mocked_history.return_Value = self.mocked_output
            output = interface.fetch("XYZ")
            mocked_history.assert_called_with(period='max', interval='1d')
            interface.fetch("ABC",fp="1w",fi="1m")
            mocked_history.assert_called_with(period='1w', interval='1m')
    
        

if __name__ == '__main__':
    main()
    