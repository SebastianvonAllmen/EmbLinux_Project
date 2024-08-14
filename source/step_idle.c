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

    puts("Connection accepted");
    sendToClientAndLog("Give me your response, waiting for Opponents response");
    
    return 0;
}

