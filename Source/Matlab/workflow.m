%% Stock Trading Agent
%
% Author:
% Elvis Payano
% 
% Date:
% May 10th, 2020
%
% Description:
% This workflow is designed to take a user defined stock and train/simulate
% a Neural Network to assess trade positions

%% Configuration
Ticker = "MSFT";

%% Configure Local Python
SysPyPath = getenv("PYTHONPATH");
LocPyPath = sprintf('%s/../Python',pwd);
addpath(LocPyPath);
if ~contains(SysPyPath,LocPyPath)
    setenv("PYTHONPATH",sprintf("%s;%s",SysPyPath,LocPyPath))
end

%% Load Training & Simulation Data
[TrainData, SimData] = LoadData(Ticker);

%% Reset Function Handle Creation
ResetTrainHandle = @()TraderReset(TrainData);
ResetSimHandle   = @()TraderReset(SimData);

%% Step Function Handle Creation
% StepTrainHandle = @(Action, Trader) TraderStep(Action, Trader, TrainData, true);
% StepSimHandle   = @(Action, Trader) TraderStep(Action, Trader, SimData, false);
