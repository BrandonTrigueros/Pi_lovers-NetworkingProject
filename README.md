# PI_Lovers

## Compile & Run

### Server compilation
1. Step into the folder of the files you want to compile
2. Type "make" into the terminal
3. Type ./main.out Server

### Client compilation
1. Step into the folder of the files you want to compile
2. Type "make" into the terminal
    - Type "make test" if you want to run all the tests
3. Run
    - Type ./main.out (legoFigure) if you want an specific figure

## Etapa 4 - Network with Intermediate Node

In this stage, the project implements a distributed network architecture with servers, clients, and an intermediate node that acts as a router.

### Components

#### Server
- Hosts LEGO figure information
- Responds to HTTP requests
- Handles figure part requests

#### Intermediate Node
- Acts as a router between clients and servers
- Maintains a routing table of available LEGO figures
- Forwards client requests to appropriate servers

#### Client
- Requests LEGO figure information
- Displays the figure parts to the user

### Compilation and Execution

#### Server compilation (etapa_4)
1. Navigate to the Server directory:
   ```
   cd etapa_4/Server
   ```
2. Compile the server:
   ```
   make
   ```
3. Run the server:
   ```
   ./Server.out
   ```

#### Intermediate Node compilation
1. Navigate to the Intermediate directory:
   ```
   cd etapa_4/Intermedio
   ```
2. Compile the intermediate node:
   ```
   make
   ```
3. Run the intermediate node:
   ```
   ./Intermediate.out
   ```

#### Client compilation (etapa_4)
1. Navigate to the Client directory:
   ```
   cd etapa_4/Cliente
   ```
2. Compile the client:
   ```
   make
   ```
3. Run the client with a specific LEGO figure name:
   ```
   ./Client.out [legoFigureName]
   ```
   
   Examples:
   ```
   ./Client.out SantaClaus
   ./Client.out Dragon
   ./Client.out BobOmb
   ./Client.out TieFighter
   ```

### Network Architecture

The etapa_4 implementation uses a three-tier architecture:
1. Clients make requests to the intermediate node
2. Intermediate node determines which server has the requested LEGO figure
3. Intermediate node forwards the request to the appropriate server
4. Server responds with the figure information
5. Intermediate node returns the response to the client

This architecture allows for horizontal scaling of servers and improved fault tolerance.