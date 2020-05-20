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
        self.m_hist = DataFrame(data=data,index=Col)
        
        cell_data = ["2020-05-18", 185.75, 186.20, 183.98, 184.91, 34415474]
        self.m_hist_c = cell_data

    def tearDown(self):
        pass
    
    def test_fetch(self):
        with self.assertRaises(TypeError):
            interface.fetch(1)
            interface.fetch("XYZ", fp=[1,2,3])
            interface.fetch("XYZ", fi=[1,2,3])

        with mock.patch('ticker.interface.yfinance.ticker.TickerBase.history') as m_history_fun:
            m_history_fun.return_Value = self.m_hist
            interface.fetch("XYZ")
            m_history_fun.assert_called_with(period='max', interval='1d')

            interface.fetch("ABC",fp="1w",fi="1m")
            m_history_fun.assert_called_with(period='1w', interval='1m')

    def test_hist2cell(self):
        invalid_input = list()
        with self.assertRaises(TypeError):
            interface.hist2cell(invalid_input)

        #interface.hist2cell(self.m_hist)
        #self.assertEqual(self.m_hist_c, interface.hist2cell(self.m_hist))

        

    
        

if __name__ == '__main__':
    main()
    