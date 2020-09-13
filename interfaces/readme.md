# Interfaces
This library houses all functionality to interact with external APIs such as those implemented by broker and database applications. The interface connection between this project and the external applications will utilze an abstract base class implementation that will allow for an easy transition between different external applications as required.

## Broker
The broker interface will provide a framework for all functionality that is required by the project to properly gather updates, and take any of the expected actions.

### Interactive Broker
Interactive Broker is a platform with a readily accessible API that can be implemented into the project using a provided *Wrapper* format. Due to the current small scale of the project implementation with this broker API is limited to single threaded with blocking functionality. This is to reduce complexity involving asynchronous or multithreaded operation  

## Database
The database interface provides a framework for all functionality that is required by the project to properly configure the neural networks as well as capture/record all actions taken during operations.

### PostgreSQL
PostgreSQL is a free relational database that has an extension for an API that allows for integration into this project. Postgres has the added capability that it is a containerized solution that allows for simpler and more controlled deployment with the use of Docker.
