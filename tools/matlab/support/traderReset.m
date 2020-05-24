%% Trader Reset
%
% Description:
% This function resets the Reinforcement Learning Environment to the
% default state to ensure a proper starting point for each training episode
%
% Author:
% Elvis Payano

function [InitObs, Trader] = traderReset(DataSet, Ticker)

%% Initialize Trader Portfolio
account = portfolio;
account = account.deposit(1000);

curDay = 10;
ind = (curDay-1):-1:(curDay-9);
%% Setup
States = [
    account.getBalance();
    account.getHoldings(Ticker);
    account.getProfitLoss();
    DataSet.Open(ind);
    DataSet.Close(ind);
    DataSet.High(ind);
    DataSet.Low(ind);
];

%% Configure Trader
Trader.Account = account;
Trader.Index   = ind;
Trader.EndInd  = height(DataSet);

%% Configure Observation
InitObs = States;
end