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
    reshape(DataSet.Open(ind),[],1);
    reshape(DataSet.Close(ind),[],1);
    reshape(DataSet.High(ind),[],1);
    reshape(DataSet.Low(ind),[],1);
];

%% Configure Trader
Trader.Account = account;
Trader.Index   = ind;
Trader.EndInd  = height(DataSet);

%% Configure Observation
InitObs = States;
end