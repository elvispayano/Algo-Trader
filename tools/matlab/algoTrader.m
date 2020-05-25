%% Stock Trading Agent
%
% Description:
% This workflow is designed to take a user defined stock and train/simulate
% a Neural Network to assess trade positions
%
% Author:
% Elvis Payano

%% Configuration
% Configuration is user defined and will establish what data is used for
% training and simulation.
Ticker = 'MSFT';

%% Load Training & Simulation Data
% Using the defied Ticker, seperate the collected data into training and
% simulation data. The training data will be used for the initial training.
% The simulation data will be used for evaluation of performance with new
% unseen data.
[TrainData, SimData] = LoadData(Ticker);

%% Environment Creation
% The RL Agent requires a defined environment that can be configured for a
% fresh run for each episode. The environment consists of an
% reset function (for initialization), a step function (for simulation),
% expected actions (taken by the agent), and expected observations (the
% data fed into the agent) in response to it's actions.
resetTrainHandle = @()traderReset(TrainData, Ticker);
stepTrainHandle = @(Action, Trader) traderStep(Action, Trader, TrainData, Ticker, true);

actionInfo = rlFiniteSetSpec(1:3);
actionInfo.Name = 'Trader Actions';

obsInfo = rlNumericSpec([39 1]);
obsInfo.Name = 'Stock Trading States';

env = rlFunctionEnv(obsInfo, actionInfo, stepTrainHandle, resetTrainHandle);

%% Agent Creation
% The agent in this design consists of an Actor (that takes the trading
% actions) and a Critic (that evaluates the actions taken). Together the
% two networks are referred to as the agent.
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

%% Agent Training & Evaluation
% Training and evaluating the designed Agent is crucial to ensure
% performance not just within a training environment with data that it has
% seen before, but to get a true sense of performance with brand new data.
% This process will allow for deficiencies to be discovered that would not
% have been found in a pure training environment.

% Training
trainOpts = rlTrainingOptions();
trainOpts.MaxEpisodes = 5e3;
trainOpts.MaxStepsPerEpisode = height(TrainData);
trainOpts.Verbose = true;
trainOpts.Plots = 'training-progress';
trainOpts.StopTrainingCriteria = 'AverageReward';
trainOpts.StopTrainingValue = 1e3;

performance = train(agent, env, trainOpts);

% Evaluation
resetEvalHandle = @()traderReset(SimData, Ticker);
stepEvalHandle  = @(Action, Trader) traderStep(Action, Trader, SimData, Ticker, false);
envEval         = rlFunctionEnv(obsInfo, actionInfo, stepEvalHandle, resetEvalHandle);

simOpts = rlSimulationOptions();
simOpts.MaxSteps = height(SimData);

exp = sim(envEval, agent, simOpts);