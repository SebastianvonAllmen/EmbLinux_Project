#include "gpio_control.h"
#include <stdio.h>

struct gpiod_chip* setup_gpio_chip(const char *chipname) {
    struct gpiod_chip *chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("gpiod_chip_open_by_name");
    }
    return chip;
}

struct gpiod_line* setup_gpio_line(struct gpiod_chip *chip, unsigned int line_number) {
    struct gpiod_line *line = gpiod_chip_get_line(chip, line_number);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
    }

    // Request the line as an output, initially set to low
    if (gpiod_line_request_output(line, "outputGpio21", 0) < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(chip);
        return NULL;
    }

    return line;
}

void set_gpio_value(struct gpiod_line *line, int value) {
    if (line) {
        gpiod_line_set_value(line, value);
    }
}

void close_gpio(struct gpiod_chip *chip, struct gpiod_line *line) {
    if (line) {
        gpiod_line_release(line);
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
}
