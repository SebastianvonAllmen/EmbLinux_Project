#include <stdio.h>
#include <string.h>    // For strlen
#include <sys/socket.h>
#include <arpa/inet.h> // For inet_addr
#include <unistd.h>    // For write, close
#include "gpio_control.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char client_message[BUFFER_SIZE];
    int read_size;
    
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
        return 1;
    }
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    
    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("Bind failed, port may be already used");
        return 1;
    }
    puts("Bind done");
    
    // Listen
    listen(socket_desc, 3);

    // GPIO Setup
    struct gpiod_chip *chip = setup_gpio_chip("gpiochip0");
    if (!chip) {
        return 1;
    }
    struct gpiod_line *line = setup_gpio_line(chip, 21);
    if (!line) {
        close_gpio(chip, line);
        return 1;
    }

    // Accept incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    if (new_socket < 0) {
        perror("Accept failed");
        close_gpio(chip, line);
        return 1;
    }
    puts("Connection accepted");
    write(new_socket, "Controll LED by writing: on,off\n", strlen("Controll LED by writing: on,off\n"));

    // Communicate with the client
    while ((read_size = recv(new_socket, client_message, BUFFER_SIZE, 0)) > 0) {
        client_message[read_size] = '\0';  // Null-terminate the received string
    
        // Check the received message and act accordingly
        if (strncmp(client_message, "on", 2) == 0) {
            set_gpio_value(line, 1); // Turn the LED on
            puts("LED turned on");
            write(new_socket, "LED turned on\n", strlen("LED turned on\n"));
        } else if (strncmp(client_message, "off", 3) == 0) {
            set_gpio_value(line, 0); // Turn the LED off
            puts("LED turned off");
            write(new_socket, "LED turned off\n", strlen("LED turned off\n"));
        } else {
            write(new_socket, "Invalid command\n", strlen("Invalid command\n"));
        }

        // Clear the message buffer
        memset(client_message, 0, BUFFER_SIZE);
    }

    if (read_size == 0) {
        puts("Client disconnected");
    } else if (read_size == -1) {
        perror("recv failed");
    }

    // Close the client socket
    close(new_socket);

    // Release GPIO line and close chip
    close_gpio(chip, line);

    return 0;
}
