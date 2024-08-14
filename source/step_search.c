#include "step_search.h"
#include "tcp_helper.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h> // For inet_addr
#include <sys/socket.h>
#include <unistd.h>    // For close
#include "tcp_helper.h"

int search(const char *server_ip) {
    if (connect_to_server(server_ip) != 0) {
        return 1;
    }  

    sendAndLog("Hello Server, i am ready to play!");

    return 0;
}
