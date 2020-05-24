%% Portfolio
%
% Description:
% This class tracks the actions taken within a portfolio. Account states
% are updated accordingly to each action taken and verifications are also
% in place to prevent undesired actions
%
% Author:
% Elvis Payano
classdef portfolio
    properties (Access = private)
        Holdings
        Balance
        Purchases
        Sell
        PnL
    end    
    methods
        %% Constructor
        % Setup class with initialized values
        function self = portfolio()
            self.Holdings = struct();
            self.Balance  = 0;
            self.PnL      = 0;
        end

        %% Buy
        % Increase quantity of a holding by a specified quantity
        function self = buy(self, stock, quantity, price)
            if ~isfield(self.Holdings, stock)
                self.Holdings.(stock).Quantity = 0;
            end
            if self.Balance < price*quantity
                self.pError('portfolio:buy','Insufficient Funds');
            end
            self.Holdings.(stock).Quantity = self.Holdings.(stock).Quantity + quantity;
            self.Balance = self.Balance - price*quantity;
        end
        
        %% Sell
        % Decrease quantity of a holding by a specified quantity
        function self = sell(self, stock, quantity, price)
            if ~isfield(self.Holdings, stock)
                self.pError('portfolio:sell', 'Insufficient Holdings');
            elseif self.Holdings.(stock).Quantity < quantity
                self.pError('portfolio:sell', 'Insufficient Holdings');
            end
            
            self.Holdings.(stock).Quantity = self.Holdings.(stock).Quantity - quantity;
            self.Balance = self.Balance + price*quantity;
        end
        
        %% Get Holdings
        % Return the available quantity of a specified holding within the
        % portfolio
        function quantity = getHoldings(self,stock)
            if ~isfield(self.Holdings, stock)
                quantity = 0;
            else
                quantity = self.Holdings.(stock).Quantity;
            end
        end
        
        %% Get Balance
        % Return the account balance of the portfolio
        function balance = getBalance(self)
            balance = self.Balance;
        end
        
        %% Get Profit & Loss
        % Return the realized profit or loss
        function profitLoss = getProfitLoss(self)
            profitLoss = self.PnL;
        end
        
        %% Deposit
        % Make a deposit to the account
        function self = deposit(self, amount)
            if amount < 0
                self.pError('portfolio:deposit','Deposit amount must be positive value');
            end
            self.Balance = self.Balance + amount;
        end
        
        %% Withdraw
        % Make a withdrawl from the account
        function self = withdraw(self, amount)
           if amount < 0
               self.pError('portfolio:withdraw','Withdraw amount must be positive value');
           end
           
           if self.Balance < amount
               self.pError('portfolio:overdraft','Insufficient Funds');
           end
           
           self.Balance = self.Balance - amount;
        end
    end
    
    methods (Access = private)
        %% Portfolio Error
        % Provide class with a simplified way to implement an error
        function pError(~,ID,Message)
            err = MException(ID, Message);
            throw(err);
        end
    end
end