#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <gpiod.h>

// Function declarations
int initialize_gpio();
int setup_gpio_chip(const char *chipname);
int setup_gpio_line(struct gpiod_chip *chip, unsigned int line_number);
void close_gpio();
void set_gpio_value(int value);

#endif // GPIO_CONTROL_H
