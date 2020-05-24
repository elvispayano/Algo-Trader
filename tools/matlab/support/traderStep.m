function [NextObs, Reward, IsDone, Trader] = traderStep(Action, Trader, DataSet, Ticker, isTrain)

%% Initialize Workspace
account = Trader.Account;
ind     = Trader.Index;
endInd  = Trader.EndInd;

%% Action & Reward
Reward = 0;
switch Action
    case 0 % Buy
        if account.getBalance() < 1000
            Reward = Reward - 1;
        else
            account = account.buy(Ticker,1,100);
        end
        
    case 1 % Hold
        
    case 2 % Sell
        if account.getHoldings(Ticker) <= 0
            Reward = Reward - 1;
        else
            account = account.sell(Ticker,1,100);
        end
end
%% Simulation Update
ind = ind + 1;

%% Output
NextObs = [
    account.getBalance();
    account.getHoldings(Ticker);
    account.getProfitLoss();
    DataSet.Open(ind);
    DataSet.Close(ind);
    DataSet.High(ind);
    DataSet.Low(ind);
];

IsDone = false;
if max(ind) >= endInd
    IsDone = true;
end

end