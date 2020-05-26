%% Trader Step
%
% Description:
% This function provides the constantly updating environment that the agent
% will be stepping through as it runs each episode
%
% Author:
% Elvis Payano

function [NextObs, Reward, IsDone, Trader] = traderStep(Action, Trader, DataSet, Ticker, isTrain)

%% Initialize Workspace
account = Trader.Account;
ind     = Trader.Index;
endInd  = Trader.EndInd;

%% Action & Reward
Reward = 0;
curPrice = randPrice(DataSet, max(ind));
switch Action
    case 1 % Buy
        if account.getBalance() < 1000
            Reward = Reward - 1;
        else
            account = account.buy(Ticker,1,curPrice);
        end
        
    case 2 % Hold
        
    case 3 % Sell
        if account.getHoldings(Ticker) <= 0
            Reward = Reward - 1;
        else
            account = account.sell(Ticker,1,curPrice);
            Reward = Reward + account.getProfitLoss()/10;
        end
end
%% Simulation Update
ind = ind + 1;

%% Output
NextObs = [
    account.getBalance();
    account.getHoldings(Ticker);
    account.getProfitLoss();
    reshape(DataSet.Open(ind),[],1);
    reshape(DataSet.Close(ind),[],1);
    reshape(DataSet.High(ind),[],1);
    reshape(DataSet.Low(ind),[],1);
    ];

Trader.Index = ind;
Trader.Account = account;

IsDone = false;
if max(ind) >= endInd - 10
    IsDone = true;
        
    fprintf('Total Profits: $%3.2f \t Account Balance: $%3.2f \t Current Holdings: %d\n', ...
        account.getProfitLoss(), ...
        account.getBalance(), ...
        account.getHoldings(Ticker));
end

end

%% Current Day Random Price
%
% Description:
% This function generates a random value between the current days high and
% low. As intraday data is not available, a random value is used to
% simulate an action taking at an arbitrary point during the day.
%
% Author:
% Elvis Payano

function curPrice = randPrice(dataSet, curDay)
highLow = [ dataSet.Low(curDay); dataSet.High(curDay)];
rng = [0; 1];
curPrice = interp1(rng, highLow, rand());
end