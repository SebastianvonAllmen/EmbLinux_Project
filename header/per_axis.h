#ifndef PER_AXIS_H
#define PER_AXIS_H

#include "step_contoller.h"

int init_LIS3DH();
void read_acceleration(int *x, int *y, int *z);
Choice read_position();

#endif // PER_AXIS_H