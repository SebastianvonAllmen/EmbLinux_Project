#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close
#include <pthread.h>
#include <fcntl.h>          // Needed for open() and O_RDWR
#include <unistd.h>         // Needed for close(), usleep(), etc.
#include <sys/ioctl.h>      // Needed for ioctl()
#include <linux/i2c-dev.h>  // Needed for I2C_SLAVE

#include "tcp_helper.h"
#include "step_contoller.h"
#include "rest_controller.h"
#include "per_axis.h"

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <server|client> [server_ip]\n", argv[0]);
        return 1;
    }

    pthread_t rest_api_thread;

    // Figure out which mode to run
    if (strcmp(argv[1], "server") == 0) { 
        // Start the REST API server in a background thread
        if (pthread_create(&rest_api_thread, NULL, start_rest_api, NULL) != 0) {
            puts("Error: Failed to create REST API thread.");
            return 1;
        }

        int ret_val = startSteps(true, NULL);

        stop_rest_api();

        pthread_join(rest_api_thread, NULL);

        return ret_val;
    } else if (strcmp(argv[1], "client") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s client <server_ip>\n", argv[0]);
            return 1;
        }

        // Extract the server IP from the second argument
        const char *server_ip = argv[2];
        return startSteps(false, server_ip);
    } else {
        fprintf(stderr, "Invalid mode: %s. Use 'server' or 'client'.\n", argv[1]);
        return 1;
    }
}
