#include "step_stop.h"
#include "tcp_helper.h"
#include "gpio_control.h"

int stop() {
    // Close the client socket
    close_client_socket();

    // Release GPIO line and close chip
    close_gpio();
}