classdef python
    
    methods (Static)
        function version = getVersion()
            env = pyenv;
            version = env.Version;
        end
        
        function history = fetch(ticker, period, interval)
            arguments
                ticker   (1,1) string
                period   (1,1) string
                interval (1,1) string
            end
            history = py.ticker.interface.fetch(py.str(ticker), py.str(period), py.str(interval));
        end
        
        function cellOut = dataframe2cell(dataframe)
            cellOut = py.ticker.interface.dataframe2cell(dataframe);
        end
    end
end