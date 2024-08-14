#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close
#include "gpio_control.h"
#include "tcp_helper.h"
#include "step_init.h"
#include "per_display.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    char client_message[BUFFER_SIZE];
    int read_size;
    
    int ret_val = init();
    if (ret_val != 0) {
        return 1;
    }

    printf("OLED example in C\n");
    demoText();
    sleep(2);
    demoGraphics();
    sleep(2);
    demoFont();

    // Accept incoming connection
    puts("Waiting for incoming connections...");
    if (accept_connection() < 0) {
        close_gpio();
        return 1;
    }

    puts("Connection accepted");
    sendToClientAndLog("Controll LED by writing: on, off");

    // Communicate with the client
    while ((read_size = receive_message(client_message, BUFFER_SIZE)) > 1) {
        // Check the received message and act accordingly
        if (strncmp(client_message, "on", 2) == 0) {
            set_gpio_value(1); // Turn the LED on
            sendToClientAndLog("LED turned on");
        } else if (strncmp(client_message, "off", 3) == 0) {
            set_gpio_value(0); // Turn the LED off
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
    close_gpio();

    return 0;
}
