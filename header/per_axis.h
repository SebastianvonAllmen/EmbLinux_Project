#ifndef PER_AXIS_H
#define PER_AXIS_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

void init_LIS3DH(int fd);
void read_acceleration(int fd, int *x, int *y, int *z);
int read_position(int fd);

#endif // PER_AXIS_H