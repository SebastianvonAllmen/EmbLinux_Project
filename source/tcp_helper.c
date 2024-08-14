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
    return 0;
}


void sendAndLog(const char *message) {
    if (gen_socket == -1) {
        puts("No socket set");
        return;
    }

    // Log the message to the console
    puts(message);

    // Send the message to the client
    write(gen_socket, message, strlen(message));
    write(gen_socket, "\n", 1);  // Ensure newline is sent after the message
}

int receive_message(char *buffer, int buffer_size) {
    if (gen_socket == -1) {
        puts("No socket set");
        return -1;
    }

    int read_size = recv(gen_socket, buffer, buffer_size, 0);
    if (read_size > 0) {
        buffer[read_size] = '\0';  // Null-terminate the received string
    } else if (read_size == 0) {
        puts("Client disconnected");
    } else if (read_size == -1) {
        perror("recv failed");
    }
    return read_size;
}

void close_socket() {
    if (gen_socket != -1) {
        close(gen_socket);
        gen_socket = -1;
    }
}

int connect_server(const char *server_ip) {
    // Create Server config
    struct sockaddr_in server;

    // Prepare the sockaddr_in structure
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888); 

    // Connect to the server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(socket_desc);
        return 1;
    }

    return 0;
}
