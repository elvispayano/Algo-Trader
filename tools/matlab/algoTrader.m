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

%% Actor, Critic Agent Creation
repOpts = rlRepresentationOptions();
repOpts.LearnRate = 1e-3;
repOpts.GradientThreshold = 1;
repOpts.UseDevice = 'gpu';

% Critic Network
criticNet = [
    imageInputLayer([39 1 1],'Name', 'State', 'Normalization', 'None')
    fullyConnectedLayer(250, 'Name', 'FC1')
    tanhLayer('Name', 'Tanh1')
    fullyConnectedLayer(250, 'Name', 'FC2')
    tanhLayer('Name', 'Tanh2')
    fullyConnectedLayer(125, 'Name', 'FC3')
    reluLayer('Name', 'Relu1')
    fullyConnectedLayer(1, 'Name', 'Output')
];

critic = rlValueRepresentation(criticNet, obsInfo,...
    'Observation', {'State'}, repOpts);

% Actor Network
actorNet = [
    imageInputLayer([39 1 1],'Name', 'State', 'Normalization', 'None')
    fullyConnectedLayer(250, 'Name', 'FC1')
    tanhLayer('Name', 'Tanh1')
    fullyConnectedLayer(250, 'Name', 'FC2')
    tanhLayer('Name', 'Tanh2')
    fullyConnectedLayer(125, 'Name', 'FC3')
    reluLayer('Name', 'Relu1')
    fullyConnectedLayer(3, 'Name', 'Action')
];

actor = rlStochasticActorRepresentation(actorNet, obsInfo, actionInfo,...
    'Observation', {'State'}, repOpts);

% Agent
agentOpts = rlACAgentOptions();
agentOpts.NumStepsToLookAhead = 64;
agentOpts.EntropyLossWeight = 0.3;
agentOpts.DiscountFactor = 0.9;

agent = rlACAgent(actor, critic, agentOpts);
