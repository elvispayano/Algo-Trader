%% Data Collection
%
% Description:
% This class handles requesting and capturing all requested stock data from
% the python ticker module. It can additionally be used for performing
% common feature extractions.
%
% Author:
% Elvis Payano

classdef dataCollection < python
    %% Private Variables
    properties (Access = private)
        dataRaw;
        dataFormatted;
    end
    
    %% Functions
    methods (Static)
        %% Constructor
        % Ensures that the required Python engine is loaded
        function self = dataCollection()
            if str2double(python.getVersion()) <= 3.5
                err = MException('dataCollection:pythonError', ...
                    'Python version 3.5+ required');
                throw(err)
            end
        end
    end
    
    methods
        %% Gather History
        % Capture historical stock data from the Python ticker module
        function self = gatherHistory(self, ticker_in, period_in, interval_in)
            arguments
                self (1,1) {isa(self,'dataCollection')}
                ticker_in (1,1) string
                period_in string {dataCollection.memberOf(period_in,{'1d','5d','1mo','3mo','6mo','1y','2y','5y','10y','ytd','max'})} = "max"
                interval_in string {dataCollection.memberOf(interval_in,{'1m','2m','5m','15m','30m','60m','90m','1h','1d','5d','1wk','1mo','3mo'})} = "1d"
            end
            
            if ~isempty(regexpi(ticker_in,'[\d\W]'))
                err = MException('dataCollection:gatherHistory:invalidInput',...
                    'Invalid Ticker Symbol format');
                throw(err)
            end
            
            ticker   = lower(ticker_in);
            period   = lower(period_in);
            interval = lower(interval_in);
            
            self.dataRaw = python.fetch(ticker, period, interval);
            self.dataFormatted = python.dataframe2cell(self.dataRaw);
        end
        
        %% Get Raw Data
        % Return historical stock data in Dataframe format
        function output = getRawData(self)
            output = self.dataRaw;
        end
        
        %% Get Formatted Data
        % Return historical stock data in 2D Python list format
        function output = getFormattedData(self)
            output = self.dataFormatted;
        end
        
        %% Get Headers
        % Returns headers for row labels (dates) and column entries (open,
        % close, etc.)
        function output = getHeaders(self)
            output = cell(1,int64(self.dataRaw.columns.size) + 1);
            output{1} = string(self.dataRaw.axes(1,1).pop().name);
            for i = 1:(length(output)-1)
                input_string = string(self.dataRaw.columns.values.item(py.int(i-1)));
                output{i+1} = strrep(input_string,' ','');
            end
        end
    end
    
    %% Member Of
    % Custom input verification checking method
    methods (Static, Access = private)
        function memberOf(input,set)
            mustBeMember(lower(input),set)
        end
    end
end