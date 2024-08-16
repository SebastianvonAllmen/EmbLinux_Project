# EmbLinux Project

This project is a networked game platform running on embedded Linux devices, such as Raspberry Pi, using GPIO and I2C interfaces. The platform includes a server and client implementation for playing a game of Rock, Paper, Scissors between two devices. Additionally, a REST API is provided for accessing game results stored in a CSV file.

## Project Overview

### Features

- **Server and Client Communication**: The server and client communicate over TCP/IP to play Rock, Paper, Scissors.
- **Game Logging**: Game results, including the choices and outcome, are logged in a CSV file (`results.csv`).
- **REST API**: A simple REST API is provided to retrieve all logged game results.
- **GPIO and I2C Integration**: The project integrates with GPIO and I2C interfaces, making it suitable for hardware interaction on embedded systems.
- **Per-Axis Control**: The `per_axis.c` file likely handles specific controls or computations related to individual axes, potentially for sensors or other peripherals.

### Project Structure

- **`main.c`**: The entry point for the application. It determines whether to run in server or client mode.
- **`source/`**: Contains the implementation files for the different modules:
  - `file_helper.c`: Provides functions for reading and writing game results to a CSV file.
  - `per_axis.c`: Manages operations or calculations on a per-axis basis, which might relate to sensor data or motor control.
  - `rest_controller.c`: Implements the REST API for retrieving game results.
  - `step_controller.c`: Controls the game flow.
  - `tcp_helper.c`: Manages TCP communication.
- **`header/`**: Contains header files with function declarations and constants used across the project.
- **`log/`**: Stores the `results.csv` file where game results are logged.
- **`doc/`**: Contains documentation for the project, providing detailed explanations and guides.

## Prerequisites

Before building and running the project, ensure you have the following dependencies installed:

```bash
sudo apt-get install gpiod libgpiod-dev
sudo apt-get install libi2c-dev i2c-tools
sudo apt-get install libmicrohttpd-dev
```

## Building the Project

1. **Create the Build Directory** (if not already present):

    ```bash
    mkdir build && mkdir log
    cd build
    ```

2. **Configure and Build the Project**:

    ```bash
    cmake ..
    make clean && make
    ```

## Running the Project

### Server Setup

1. **Start the Server**:
    - Run the server on the device that will act as the host (e.g., `146.136.88.38`):

    ```bash
    ./EmbLinux_Project server
    ```

2. **Start the REST API**:
    - The server will also start a REST API on port `8080` that you can use to query game results.

### Client Setup

1. **Start the Client**:
    - On another device, start the client and connect to the server using its IP address:

    ```bash
    ./EmbLinux_Project client 146.136.88.38
    ```

### Workflow

1. **First**, start the server program on the server device.
2. **Then**, start the client program on the client device.
3. The client and server will communicate to play a game of Rock, Paper, Scissors. The results will be logged in `results.csv`.
4. You can retrieve the results using the REST API by accessing `http://<server-ip>:8080/`.

## Testing and Debugging

### Free Ports

To free ports `8888` and `8080` before running the server and client:

```bash
sudo lsof -t -i:8888 | xargs sudo kill && sudo lsof -t -i:8080 | xargs sudo kill
```

### Testing TCP Connection

To test the TCP connection on port `8888`:

```bash
nc 146.136.88.38 8888
```

## Device IP Addresses

For reference, the IP addresses of the devices in your setup are:

- `146.136.88.38` - SvA (Server)
- `146.136.88.26` - RC (Client)
- `146.136.90.42` - SvA Host

## Useful Commands

### Install Required Packages

```bash
sudo apt-get install gpiod libgpiod-dev
sudo apt-get install libi2c-dev i2c-tools
sudo apt-get install libmicrohttpd-dev
```

### Executing the Client Program

```bash
./EmbLinux_Project client 146.136.88.38
```

### Freeing Ports

```bash
sudo lsof -t -i:8888 | xargs sudo kill && sudo lsof -t -i:8080 | xargs sudo kill
```

### Testing Network Connection

```bash
nc 146.136.88.38 8888
```