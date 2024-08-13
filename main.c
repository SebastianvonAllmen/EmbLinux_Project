#include <stdio.h>
#include <string.h>    // For strlen
#include <sys/socket.h>
#include <arpa/inet.h> // For inet_addr
#include <unistd.h>    // For write and close
#include <gpiod.h>     // For GPIO

int main(int argc, char *argv[]) {
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char *message;

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
    struct gpiod_chip *chip = gpiod_chip_open_by_name("gpiochip0");
    if (!chip) {
        perror("gpiod_chip_open_by_name");
        return 1;
    }
    struct gpiod_line *line = gpiod_chip_get_line(chip, 21);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return 1;
    }

    // Request the line as an output, initially set to low
    if (gpiod_line_request_output(line, "outputGpio21", 0) < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(chip);
        return 1;
    }

    // Accept incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        puts("Connection accepted");

        // Reply to the client
        message = "Hello Client, I have received your connection. But I have to go now, bye\n";
        write(new_socket, message, strlen(message));

        // Check the current value of GPIO line 21
        int value = gpiod_line_get_value(line);
        if (value < 0) {
            perror("gpiod_line_get_value");
        } else if (value == 0) {
            gpiod_line_set_value(line, 1); // Set the GPIO line high
            puts("GPIO 21 set to high");
        } else {
            gpiod_line_set_value(line, 0); // Set the GPIO line low
            puts("GPIO 21 set to low");
        }

        // Close the client socket
        close(new_socket);
    }

    // Release GPIO line and close chip
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    if (new_socket < 0) {
        perror("Accept failed");
        return 1;
    }

    return 0;
}
