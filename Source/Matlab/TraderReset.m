function [InitObs, Trader] = TraderReset(DataSet)

%% Initialize Trader Constants
Cash = 1000; % Start off with $1k
Holdings = 0;
ProfitLoss = 0;
CurDay = 10;

Index = (CurDay-1):-1:(CurDay-9);
%% Setup
States = [
    Cash;
    Holdings;
    ProfitLoss;
    DataSet.Open(Index);
    DataSet.Close(Index);
    DataSet.High(Index);
    DataSet.Low(Index);
];

%% Configure Trader
Trader.States = States;
Trader.Index  = CurDay;

%% Configure Observation
InitObs = States;
end