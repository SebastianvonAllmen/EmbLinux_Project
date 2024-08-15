#include <stdio.h>

#include "step_contoller.h"
#include "tcp_helper.h"
#include "gpio_control.h"

bool is_server = false;
char* server_ip;

int startSteps(const bool cmd_is_server, const char* cmd_server_ip) {
    is_server = cmd_is_server;
    server_ip = cmd_server_ip;

    int ret_val = initStep();

    if (ret_val != 0) {
        return 1;
    }

    if (is_server) {
        ret_val = idleStep();

        if (ret_val != 0) {
            return 1;
        }
    } else {
        // TODO, pot check for null ip, but need to figure out where
        ret_val = searchStep(server_ip);

        if (ret_val != 0) {
            return 1;
        }
    }

    chooseStep(is_server);

    //waitStep();

    stopStep();

    return 0;
}

int initStep() {
    // Initialize TCP and start listening on port 8888
    int ret_val = initialize_tcp(8888);
    if (ret_val != 0) {
        return 1;
    }

    ret_val = initialize_gpio();
    if (ret_val != 0) {
        return 1;
    }
    

    return 0;
}

int idleStep() {
    // Accept incoming connection
    puts("Waiting for incoming connections...");
    if (accept_connection() < 0) {
        close_gpio();
        return 1;
    }

    sendAndLog("Hello Client, I am ready to play!");
    
    return 0;
}


int searchStep(const char *server_ip) {
    if (connect_to_server(server_ip) != 0) {
        return 1;
    }  

    sendAndLog("Hello Server, i am ready to play!");

    return 0;
}

int chooseStep(bool is_server) {
    // TODO start the background thread in which to potentially receive opponent choice

    // Simulate player choice
    if (is_server) {
        sleep(2);
        sendAndLog("1");
    } else {
        sleep(4);
        sendAndLog("4");
    }
}


int stopStep() {
    // Close the client socket
    close_socket();

    // Release GPIO line and close chip
    close_gpio();
}