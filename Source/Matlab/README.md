# MATLAB
Development & Training Platform

# Overview
This tool suite is utilized to develop a functioning trading network and train it to utilize specified trading strategies.

# Training Strategy
Each NN is trained and validated against historical stock data. The strategy is tested against an older historical data set, and validated against more current data; using approximately an 80% split. This broad data set is chose to hopefully capture large economic crises and account for that within our performance metrics.

## Positive Activity
During training, the NN will be rewarded not just on the overall performance/profit, but also for taking positive actions such as minimizing losses when wild swings occur.

## Negative Activity
On the otherhand, the NN will be penalized for making unsatisfactory actions, such as attempting to buy holdings with insufficient funds or attempting to sell holdings with no ownership.

# Neural Network Actions
The Network is allowed to take the same 3 positions as any trader.

## Long
The NN can decide to go long on a stock and can place a buy order to increase its stake in any holding. Attempting to buy a holding with insufficient funds is perceived as a negative activity.

## Short
The NN can alternatively decide to short a stock and decrease its stake in any holding. Attempting to sell a holding with no stake is perceived as a negative activity.

## Hold
The NN is also give the option to hold its position and neither buy nor sell holdings during the current trading window.

# Trading Strategy
(TBD)