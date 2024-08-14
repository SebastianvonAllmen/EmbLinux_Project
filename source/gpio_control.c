#include "gpio_control.h"
#include <stdio.h>

struct gpiod_chip *chip;
struct gpiod_line *line;


int initialize_gpio() {
    // GPIO Setup
    int ret_val = setup_gpio_chip("gpiochip0");
    if (ret_val != 0) {
        return 1;
    }
    ret_val = setup_gpio_line(chip, 21);
    if (ret_val != 0) {
        close_gpio(chip, line);
        return 1;
    }
    return 0;
}

int setup_gpio_chip(const char *chipname) {
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("gpiod_chip_open_by_name");
    }

    if (!chip) {
        return 1;
    }

    return 0;
}

int setup_gpio_line(struct gpiod_chip *chip, unsigned int line_number) {
    line = gpiod_chip_get_line(chip, line_number);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
    }

    // Request the line as an output, initially set to low
    if (gpiod_line_request_output(line, "outputGpio21", 0) < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(chip);
        return 1;
    }

    if (!line) {
        close_gpio(chip, line);
        return 1;
    }

    return 0;
}

void set_gpio_value(int value) {
    if (line) {
        gpiod_line_set_value(line, value);
    }
}

void close_gpio() {
    if (line) {
        gpiod_line_release(line);
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
}
