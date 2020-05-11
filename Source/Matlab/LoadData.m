%% Ticker Loading Function
%
% Author:
% Elvis Payano
% 
% Date:
% May 10th, 2020
%
% Description:
% This function will load historic ticker data for the requested symbol.
% Additionally, it splits the captured data into training data and testing
% data for validation.

function [Train, Sim] = LoadData(Ticker,Opts)
arguments
    Ticker string
    Opts.SplitFactor (1,1) double {mustBeNumeric} = 0.8
end
%% Load Ticker Data
% Get captured data and return in a table format. Implementation requires
% data to already be captured in a csv format. Future implementations
% should fetch data directly from a source and configure into a table
% format.
tick = py.str(Ticker);
RawData = py.Ticker.FetchHistory(tick);

headers = {'Date','Open','High','Low','Close','Volume'};
Data = struct();
for i = 1:length(headers)
    if contains(headers{i},'Date')
        Data.(headers{i}) = datetime([],[],[]);
    else
        Data.(headers{i}) = [];
    end
end
for i = 1:length(RawData)
    temp = RawData(i).pop();
    for j = 1:length(headers)
        if contains(headers{j},'Date')
            Data.(headers{j})(end+1) = datetime(string(temp(j).pop));
        else
            Data.(headers{j})(end+1) = double(temp(j).pop);
        end
        if i == length(RawData)
            Data.(headers{j}) = reshape(Data.(headers{j}),[],1);
        end
    end
end

%% Determine Data Time
date_start = Data.Date(1);
date_end   = Data.Date(end);
total_time = floor(days(date_end-date_start));

train_time = total_time*Opts.SplitFactor;
sim_time   = total_time*(1-Opts.SplitFactor);

%% Capture Data for Simulation & Training
sim_start_date = date_end - sim_time;
sim_end_date = date_start + train_time;
sim_data = Data.Date > sim_start_date;
train_data   = Data.Date < sim_end_date;

Sim = struct();
Train = struct();
for i = 1:length(headers)
    Sim.(headers{i}) = Data.(headers{i})(sim_data);
    Train.(headers{i}) = Data.(headers{i})(train_data);
end

end