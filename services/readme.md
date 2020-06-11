## Docker Services
These services will operate the backend of the trader project. Each service that is needed should be included in this document with a description of anything needed to configure the service.

## SQL Database
The current implementation is utilizing a postgreSQL docker container that will contain all the neural network configurations and records during operation.

### Setup
To ensure proper utilization of the SQL docker container a persistent volume must first be created.

> docker volume create postgres-db

Once successfully created, utilize docker compose to startup the database

> docker-compose up -d