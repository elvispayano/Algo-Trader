%% MATLAB 2 Python Interface
%
% Description:
% This class provides the functionality to interface with specific python
% modules that have been configured as part of this project. It also
% handles  incoming data type conversion to ensure that the functions are
% used as intended and simplify the coding required on the MATLAB
% implementation side.
%
% Author:
% Elvis Payano

classdef python
    %% Python Function Definitions
    methods (Static)
        %% Get Version
        % Get the version number of the currently loaded Python engine
        function version = getVersion()
            env = pyenv;
            version = env.Version;
        end
        
        %% Fetch
        % Get historical ticker data for the specified period and interval
        % from the project ticker module
        function history = fetch(ticker, period, interval)
            arguments
                ticker   (1,1) string
                period   (1,1) string
                interval (1,1) string
            end
            history = py.ticker.interface.fetch(py.str(ticker), py.str(period), py.str(interval));
        end
        
        %% Dataframe 2 Cell
        % Convert the Pandas Dataframe output to a 2D python array (list of
        % lists) that can be iterated through for simpler data extraction
        function cellOut = dataframe2cell(dataframe)
            cellOut = py.ticker.interface.dataframe2cell(dataframe);
        end
    end
end