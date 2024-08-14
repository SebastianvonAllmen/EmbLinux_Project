#include "step_init.h"
#include "tcp_helper.h"
#include "gpio_control.h"


int init() {
    // Initialize TCP and start listening on port 8888
    int ret_val = initialize_tcp(8888);
    if (ret_val != 0) {
        return 1;
    }

    ret_val = initialize_gpio();
    if (ret_val != 0) {
        return 1;
    }
    

    return 0;
}