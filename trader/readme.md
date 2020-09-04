# Algo-Trader
Created an initial C++ environment that provides a modular design and unit testing. The modular design will allow each unique section of code to be isolated into independent libraries. The unit testing is conducted through a separate executable to reduce the overall future size of the project binary.

# Libraries
This initial implementation splits the C++ into 3 distinct libraries and implementation of future libraries will should remain as self contained entities that are utilized and linked by the top-level CMake file

## GUI
This library contains all code that deploys the functions made throughout the project to provide a front end that will allow custom execution by the user

## Interfaces
This library contains all code that will interact with external services such as databases and broker APIs.

## Trader
This library is accessed directly from main and will execute all the processes/algorithms that is expected. Additionally, this houses the Neural Network that will make all trading decisions.

## Utilities
This library is the backbone of the project and will contain all types and common functionality that is independent of a any other higher level library. 

## Tests
This library does not link to the main project, nor is it linked to any other included. Instead it itself calls upon the other libraries to generate a seperate executable that will run unit testing on as much functionality as possible.