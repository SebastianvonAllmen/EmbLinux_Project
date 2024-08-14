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
    // Check if the correct number of arguments is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <server|client> [server_ip]\n", argv[0]);
        return 1;
    }
    
    int ret_val = init();
    if (ret_val != 0) {
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) { 
        // Server mode
        ret_val = idle();
        if (ret_val != 0) {
            return 1;
        }
    } else if (strcmp(argv[1], "client") == 0) {
        // Client mode
        if (argc < 3) {
            fprintf(stderr, "Usage: %s client <server_ip>\n", argv[0]);
            stop();
            return 1;
        }

        // Extract the server IP from the second argument
        const char *server_ip = argv[2];

        ret_val = search(server_ip);
        if (ret_val != 0) {
            stop();
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid mode: %s. Use 'server' or 'client'.\n", argv[1]);
        stop();
        return 1;
    }

    // GAMELOOP

    stop();

    return 0;
}
