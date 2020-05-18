# Import Standard Modules
from unittest import TestCase, main, mock

# Import Custom Modules
from ticker import ticker

class TestTickerFetch(TestCase):
    def test_input_validation(self):
        output = {
            "Datetime": 1,
            "Open" : 1,
            "High" : 1,
            "Low" : 1,
            "Close": 1,
            "Volume": 1,
        }
        with mock.patch('yf') as mocked_yf:
            mocked_yf.return_value.ticker.return_Value = output
            self.assertEqual(ticker.fetch("XYZ"),output)

        self.assertRaises(TypeError, ticker.fetch, 1)
        self.assertRaises(TypeError, ticker.fetch, True)
        self.assertRaises(TypeError, ticker.fetch, list())
        self.assertRaises(TypeError, ticker.fetch, dict())
        ticker.fetch("XYZ")
    
        

if __name__ == '__main__':
    main()