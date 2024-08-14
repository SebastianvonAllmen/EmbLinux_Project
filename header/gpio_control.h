#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <gpiod.h>

// Function declarations
struct gpiod_chip* setup_gpio_chip(const char *chipname);
struct gpiod_line* setup_gpio_line(struct gpiod_chip *chip, unsigned int line_number);
void close_gpio(struct gpiod_chip *chip, struct gpiod_line *line);
void set_gpio_value(struct gpiod_line *line, int value);

#endif // GPIO_CONTROL_H
