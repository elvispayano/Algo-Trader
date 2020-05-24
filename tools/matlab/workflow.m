%% Stock Trading Agent
%
% Description:
% This workflow is designed to take a user defined stock and train/simulate
% a Neural Network to assess trade positions
%
% Author:
% Elvis Payano

%% Configuration
Ticker = "MSFT";

%% Load Training & Simulation Data
[TrainData, SimData] = LoadData(Ticker);

%% Trader Handle Simulation Creation
resetTrainHandle = @()traderReset(TrainData, Ticker);
stepTrainHandle = @(Action, Trader) traderStep(Action, Trader, TrainData, Ticker, true);

%% Environment Creation
actionInfo = rlFiniteSetSpec(1:3);
actionInfo.Name = 'Trader Actions';

obsInfo = rlNumericSpec([39 1]);
obsInfo.Name = 'Stock Trading States';

env = rlFunctionEnv(obsInfo, actionInfo, stepTrainHandle, resetTrainHandle);
