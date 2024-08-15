#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close
#include <fcntl.h>          // Needed for open() and O_RDWR
#include <unistd.h>         // Needed for close(), usleep(), etc.
#include <sys/ioctl.h>      // Needed for ioctl()
#include <linux/i2c-dev.h>  // Needed for I2C_SLAVE
#include "gpio_control.h"
#include "tcp_helper.h"
#include "step_contoller.h"
#include "per_axis.h"

#define LIS3DH_ADDR 0x18   // I2C address of the LIS3DH

int main(int argc, char *argv[]) {

    int fd;
    char *filename = "/dev/i2c-1";

    // Open the I2C bus
    if ((fd = open(filename, O_RDWR)) < 0) {
        printf("Failed to open the I2C bus\n");
        return 1;
    }

    // Connect to the LIS3DH sensor
    if (ioctl(fd, I2C_SLAVE, LIS3DH_ADDR) < 0) {
        printf("Failed to connect to the LIS3DH sensor\n");
        close(fd);
        return 1;
    }

    // Initialize the LIS3DH sensor
    init_LIS3DH(fd);

    // Variables to hold the X, Y, Z acceleration data
    int x, y, z;

    while (1) {
        // Read the acceleration data
        read_acceleration(fd, &x, &y, &z);

        // Print the acceleration values (in mg)
        printf("X: %d mg, Y: %d mg, Z: %d mg\n", x, y, z);

        int pos = read_position(fd);
        printf("Position: %d\n", pos);
        switch(pos) {
            case 0:
                printf("X-AXIS\n");
                printf("Rock\n");
                break;
            case 1:
                printf("Y-AXIS\n");
                printf("Scissors\n");
                break;
            case 2:
                printf("Z-AXIS\n");                
                printf("Paper\n");
                break;
            default:
                printf("Something went wrong step bro\n");
                break;
            }       

        // Delay for a short period (e.g., 200ms)
        usleep(200000);
    }

    // Close the I2C bus
    close(fd);


    // Check if the correct number of arguments is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <server|client> [server_ip]\n", argv[0]);
        return 1;
    }

    // Figure out which mode to run
    if (strcmp(argv[1], "server") == 0) { 
        return startSteps(true, NULL);
    } else if (strcmp(argv[1], "client") == 0) {
        // Client mode
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
