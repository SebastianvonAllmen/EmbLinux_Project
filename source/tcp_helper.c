#include "tcp_helper.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int gen_socket = -1;
static int socket_desc = -1;

int initialize_tcp(int port) {
    struct sockaddr_in server;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("Bind failed, port may be already used");
        return -1;
    }
    puts("Bind done");

    if (listen(socket_desc, 3) < 0) {
        perror("Listen failed");
        return -1;
    }

    return 0;
}

int accept_connection() {
    struct sockaddr_in client;
    socklen_t c = sizeof(struct sockaddr_in);

    gen_socket = accept(socket_desc, (struct sockaddr *)&client, &c);
    if (gen_socket < 0) {
        perror("Accept failed");
        return -1;
    }

    puts("Client successfully initialized connection");
    return 0;
}


void sendAndLog(const char *message, bool do_log) {
    if (gen_socket == -1) {
        puts("No socket set");
        return;
    }

    if (do_log) {
        puts(message);
    }

    char buffer[1024]; 
    snprintf(buffer, sizeof(buffer), "%s\n", message);
    write(gen_socket, buffer, strlen(buffer));
}

int receive_message(char *buffer, int buffer_size) {
    if (gen_socket == -1) {
        puts("No socket set");
        return -1;
    }

    int read_size = 0;
    do {
        read_size = recv(gen_socket, buffer, buffer_size - 1, 0); // buffer_size - 1 to leave space for null-terminator
        if (read_size > 0) {
            buffer[read_size] = '\0';  // Null-terminate the received string

            // Trim whitespace and check if the message is empty or just a newline
            char *ptr = buffer;
            while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r') {
                ptr++;
            }

            if (*ptr != '\0') {
                // A valid message was received
                return read_size;
            } else {
                // Received an empty message or just whitespace, continue waiting
                puts("Received empty message or newline, waiting for valid message...");
            }
        } else if (read_size == 0) {
            puts("Client disconnected");
            return 0;
        } else if (read_size == -1) {
            perror("recv failed");
            return -1;
        }
    } while (1);

    // In case of unexpected exit from loop (shouldn't happen)
    return -1;
}

void close_socket() {
    if (gen_socket != -1) {
        close(gen_socket);
        gen_socket = -1;
    }
}

int connect_to_server(const char *server_ip) {
    int client_socket;
    struct sockaddr_in server;

    // Create a new socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        return -1;
    }

    // Prepare the sockaddr_in structure
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888); 

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(client_socket);
        return -1;
    }

    puts("Successfully connected to Server");

    // Store the connected socket descriptor in gen_socket if needed
    gen_socket = client_socket;

    return 0;
}


