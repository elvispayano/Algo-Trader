%% Ticker Loading Function
%
% Description:
% This function will load historic ticker data for the requested symbol.
% Additionally, it splits the captured data into training data and testing
% data for validation.
%
% Author:
% Elvis Payano

function [TrainData, SimData] = LoadData(ticker,Opts)
arguments
    ticker string
    Opts.SplitFactor (1,1) double {mustBeNumeric} = 0.8
end
%% Load Ticker Data
% Get captured data and return in a table format. Implementation requires
% data to already be captured in a csv format. Future implementations
% should fetch data directly from a source and configure into a table
% format.
% Ensure that valid python engine is available
dC = dataCollection;
dC = dC.gatherHistory(ticker, 'max', '1d');
pData = dC.getFormattedData();
headers = dC.getHeaders();

%% Generate Structure Fields
Data = struct();
% Header Sizes
Data.(headers{1}) = datetime([], [], []);
for i = 1:(length(headers)-1)
    Data.(headers{i+1}) = [];
end

for i = 1:length(pData)
    entry = cell(pData.pop());
    for j = 1:length(entry)
        if isa(entry{j},'py.str')
            Data.(headers{j})(end+1) = datetime(string(entry{j}));
        else
            Data.(headers{j})(end+1) = double(entry{j});
        end
    end
end

%% Split Data Sets
History =  sortrows(struct2table(Data));

% Desired data split based on amount of entries available
rng = 1:1:length(History.Date);
sim_data    = rng < length(History.Date)*(1-Opts.SplitFactor);

Sim = struct();
Train = struct();
for i = 1:length(headers)
    Sim.(headers{i}) = reshape(History.(headers{i})(sim_data),[],1);
    Train.(headers{i}) = reshape(History.(headers{i})(~sim_data),[],1);
end

%% Output
SimData = sortrows(struct2table(Sim));
TrainData = sortrows(struct2table(Train));
end