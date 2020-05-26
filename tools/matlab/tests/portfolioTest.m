%% Portfolio Test
%
% Description:
% Test suite for the Portfolio class
%
% Author:
% Elvis Payano

classdef portfolioTest < matlab.unittest.TestCase
    properties (Access = private)
        obj
    end
    
    properties (Access = private, Constant)
       STK = 'XYZ';
    end
    
    methods (TestClassSetup)
        %% Portfolio Construction
        % Generate a portfolio and ensure expected starting conditions
        function createAccount(tc)
            tc.obj = portfolio;
            tc.assertClass(tc.obj, 'portfolio');
            
            % Instantiate with 0 holdings & 0 Balance
            tc.assertEqual(tc.obj.getHoldings(tc.STK), 0)
            tc.assertEqual(tc.obj.getBalance(), 0)
        end
    end
    
    methods (Test)
        %% Test Transfers
        % Verify performance of deposit and withdrawl functions
        function testTransfers(tc)
            % Testing Invalid Transfer Requests
            tc.verifyError(@()tc.obj.deposit(-50), 'portfolio:deposit')
            tc.verifyError(@()tc.obj.withdraw(-50), 'portfolio:withdraw')
            
            % Testing Valid Deposit
            tc.obj = tc.obj.deposit(200);
            tc.verifyEqual(tc.obj.getBalance(), 200)
            
            % Testing Valid Withdraw
            tc.obj = tc.obj.withdraw(100);
            tc.verifyEqual(tc.obj.getBalance(), 100)
            
            % Testing Overdraft
            tc.verifyError(@()tc.obj.withdraw(200), 'portfolio:overdraft')

        end
        
        %% Test Trading
        % Verify performance of buy and sell functions
        function testTrading(tc)
            % Attempt to purchase stock with insufficient funds
            tc.verifyError(@()tc.obj.buy(tc.STK, 1, 100), 'portfolio:buy')
            
            % Attempt to sell stock not owned
            tc.verifyError(@()tc.obj.sell(tc.STK, 1, 100), 'portfolio:sell')
            
            % Adding funds
            tc.obj = tc.obj.deposit(1000);
            
            % Test Purchasing
            tc.obj = tc.obj.buy(tc.STK, 1, 100);
            tc.verifyEqual(tc.obj.getHoldings(tc.STK), 1)
            tc.verifyEqual(tc.obj.getBalance(), 900)
            
            % Test Selling
            tc.obj = tc.obj.sell(tc.STK, 1, 100);
            tc.verifyEqual(tc.obj.getHoldings(tc.STK), 0)
            tc.verifyEqual(tc.obj.getBalance(), 1000)
        end
        
        %% Test Profit/Loss Analysis
        % Validate Profit calculation
        function testProfit(tc)
            % Funds required for valid trades
            tc.obj = tc.obj.deposit(1000);
            
            % Buy and Sell a Holding
            tc.obj = tc.obj.buy(tc.STK, 1, 100);
            tc.obj = tc.obj.sell(tc.STK, 1, 110);
            
            % Verify $10 profit
            tc.verifyEqual(tc.obj.getProfitLoss(), 10);
            tc.verifyEqual(tc.obj.getBalance(), 1010);
        end
        
        % Validate Loss calculation
        function testLoss(tc)
            % Funds required for valid trades
            tc.obj = tc.obj.deposit(1000);
            
            % Buy and Sell a Holding
            tc.obj = tc.obj.buy(tc.STK, 1, 100);
            tc.obj = tc.obj.sell(tc.STK, 1, 90);
            
            % Verify $10 profit
            tc.verifyEqual(tc.obj.getProfitLoss(), -10);
            tc.verifyEqual(tc.obj.getBalance(), 990);
        end
        
        % Validate Multi-trade calculation
        function testMultiTrade(tc)
            % Funds required for valid trades
            tc.obj = tc.obj.deposit(1000);
            
            % Multiple buys of a holding
            tc.obj = tc.obj.buy(tc.STK, 3, 100);
            tc.obj = tc.obj.buy(tc.STK, 5, 105);
            
            % Multiple sells of a holding
            tc.obj = tc.obj.sell(tc.STK, 4, 110);
            tc.verifyEqual(tc.obj.getProfitLoss(), 35);
            
            tc.obj = tc.obj.sell(tc.STK, 2, 100);
            tc.verifyEqual(tc.obj.getProfitLoss(), 25);
            tc.verifyEqual(tc.obj.getBalance(), 815);
        end
    end
end