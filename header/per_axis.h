#ifndef PER_AXIS_H
#define PER_AXIS_H

#define LIS3DH_ADDR 0x18   // I2C address of the LIS3DH

void init_LIS3DH(int fd);
void read_acceleration(int fd, int *x, int *y, int *z);
int read_position(int fd);

#endif // PER_AXIS_H