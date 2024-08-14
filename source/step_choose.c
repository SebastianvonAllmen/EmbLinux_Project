#include "step_choose.h"
#include "tcp_helper.h"

int choose(bool is_server) {
    // TODO start the background thread in which to potentially receive opponent choice

    // Simulate player choice
    if (is_server) {
        sleep(2);
        sendAndLog("1");
    } else {
        sleep(4);
        sendAndLog("4");
    }
}