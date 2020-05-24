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
        if i == length(pData)
            Data.(headers{j}) = reshape(Data.(headers{j}),[],1);
        end
    end
end

History =  sortrows(struct2table(Data));

%% Determine Data Time
date_start = History.Date(1);
date_end   = History.Date(end);
total_time = floor(days(date_end-date_start));

train_time = total_time*Opts.SplitFactor;
sim_time   = total_time*(1-Opts.SplitFactor);

%% Capture Data for Simulation & Training
sim_start_date = date_end - sim_time;
sim_end_date = date_start + train_time;

sim_data    = History.Date > sim_start_date;
train_data  = History.Date < sim_end_date;

Sim = struct();
Train = struct();
for i = 1:length(headers)
    Sim.(headers{i}) = History.(headers{i})(sim_data);
    Train.(headers{i}) = History.(headers{i})(train_data);
end

SimData = struct2table(Sim);
TrainData = struct2table(Train);
end