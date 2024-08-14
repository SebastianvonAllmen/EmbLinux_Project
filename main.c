#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close
#include "gpio_control.h"
#include "tcp_helper.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char client_message[BUFFER_SIZE];
    int read_size;
    
    // Initialize TCP and start listening on port 8888
    int ret_val = initialize_tcp(8888);
    if (ret_val < 0) {
        return 1;
    }

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
    if (accept_connection() < 0) {
        close_gpio(chip, line);
        return 1;
    }

    puts("Connection accepted");
    sendToClientAndLog("Controll LED by writing: on, off");

    // Communicate with the client
    while ((read_size = receive_message(client_message, BUFFER_SIZE)) > 0) {
        // Check the received message and act accordingly
        if (strncmp(client_message, "on", 2) == 0) {
            set_gpio_value(line, 1); // Turn the LED on
            sendToClientAndLog("LED turned on");
        } else if (strncmp(client_message, "off", 3) == 0) {
            set_gpio_value(line, 0); // Turn the LED off
            sendToClientAndLog("LED turned off");
        } else {
            sendToClientAndLog("Invalid command");
        }

        // Clear the message buffer
        memset(client_message, 0, BUFFER_SIZE);
    }

    // Close the client socket
    close_client_socket();

    // Release GPIO line and close chip
    close_gpio(chip, line);

    return 0;
}
