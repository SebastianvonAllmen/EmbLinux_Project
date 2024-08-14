#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close
#include "gpio_control.h"
#include "tcp_helper.h"
#include "step_init.h"
#include "step_idle.h"
#include "step_search.h"
#include "step_stop.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char client_message[BUFFER_SIZE];
    int read_size;

    // Check if the correct number of arguments is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <server|client> [server_ip]\n", argv[0]);
        return 1;
    }
    
    int ret_val = init();
    if (ret_val != 0) {
        return 1;
    }

    if (true) { // TODO, figure out when to search and when to wait for a incomming connection
        ret_val = idle();
        if (ret_val != 0) {
            return 1;
        }
    } else {
        ret_val = search();
        if (ret_val != 0) {
            return 1;
        }
    }

    // Communicate with the client
    while ((read_size = receive_message(client_message, BUFFER_SIZE)) > 0) {
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

    stop();

    return 0;
}
