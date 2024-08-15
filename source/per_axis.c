#include <stdio.h>
#include <stdint.h>  // Include this to define int16_t, uint16_t, etc.
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define LIS3DH_ADDR 0x18   // I2C address of the LIS3DH
#define CTRL_REG1 0x20     // Control register 1
#define CTRL_REG4 0x23     // Control register 4
#define OUT_X_L 0x28       // X-axis data register (low byte)

// Function to initialize the LIS3DH sensor
void init_LIS3DH(int fd) {
    char config[2];
    
    // Set CTRL_REG1: 100Hz, enable all axes
    config[0] = CTRL_REG1;
    config[1] = 0x57;
    write(fd, config, 2);
    
    // Set CTRL_REG4: +/- 2g range, High-resolution mode
    config[0] = CTRL_REG4;
    config[1] = 0x08;
    write(fd, config, 2);
}

// Function to read acceleration data from the LIS3DH sensor
void read_acceleration(int fd, int *x, int *y, int *z) {
    char reg[1] = {OUT_X_L | 0x80};  // | 0x80 to enable auto-increment
    char data[6];

    // Write the register address
    write(fd, reg, 1);

    // Read 6 bytes of acceleration data (X, Y, Z)
    if (read(fd, data, 6) != 6) {
        printf("Error: Input/Output error\n");
    } else {
        // Convert the data to 16-bit integers
        *x = (int16_t)((data[1] << 8) | data[0]);
        *y = (int16_t)((data[3] << 8) | data[2]);
        *z = (int16_t)((data[5] << 8) | data[4]);
    }
}


// Function to read acceleration data from the LIS3DH sensor
int read_position(int fd) {
    char reg[1] = {OUT_X_L | 0x80};  // | 0x80 to enable auto-increment
    char data[6];

    int x;
    int y;
    int z;

    int position = 0; 

    // Write the register address
    write(fd, reg, 1);

    // Read 6 bytes of acceleration data (X, Y, Z)
    if (read(fd, data, 6) != 6) {
        printf("Error: Input/Output error\n");
    } else {
        // Convert the data to 16-bit integers
        x = abs((int16_t)((data[1] << 8) | data[0]));
        y = abs((int16_t)((data[3] << 8) | data[2]));
        z = abs((int16_t)((data[5] << 8) | data[4]));
    }

    // Check if x is greater than both y and z
    if (x > y && x > z) {
        position = 0;
    } else if (y > x && y > z) {
        position = 1;
    } else if (z > x && z > y) {
        position = 2;
    } else {
        printf("There is a tie in the acceleration values.\n");
        position = 3;
    }

    return position;
}