#include "step_idle.h"
#include "tcp_helper.h"
#include "gpio_control.h"

int idle() {
    // Accept incoming connection
    puts("Waiting for incoming connections...");
    if (accept_connection() < 0) {
        close_gpio();
        return 1;
    }

    sendAndLog("Hello Client, I am ready to play!");
    
    return 0;
}

