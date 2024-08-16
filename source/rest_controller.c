#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <microhttpd.h>

#include "rest_controller.h"


#define REST_PORT 8080

static volatile bool server_running = true; // Static global flag to control the REST API thread

void *start_rest_api(void *arg) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, REST_PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        puts("Failed to start REST API server");
        pthread_exit(NULL);
    }

    printf("REST API server running on port %d\n", REST_PORT);

    // Run the server loop until the flag is set to false
    while (server_running) {
        sleep(1);  // Sleep for a short period to avoid busy-waiting
    }

    MHD_stop_daemon(daemon);
    printf("REST API server shutting down.\n\n");
    pthread_exit(NULL);
}

void stop_rest_api(void) {
    server_running = false;
}

enum MHD_Result answer_to_connection(void *cls, struct MHD_Connection *connection,
                                     const char *url, const char *method,
                                     const char *version, const char *upload_data,
                                     size_t *upload_data_size, void **con_cls) {
    const char *title = "Welcome to the ever lasting War between AI and Humans\n"
                        "This page allows you to access all results from every game ever played against this AI\n"
                        "CSV Structure: {time [ms], choice server, choice client, did_ai_win}\n";

    const char *text = "1234023, 0, 1, true\n";

    // Allocate enough space for the concatenated string
    size_t response_size = strlen(title) + strlen(text) + 1; // +1 for the null terminator
    char *response = (char *)malloc(response_size);

    if (response == NULL) {
        return MHD_NO; // Failed to allocate memory
    }

    // Concatenate title and text into the response
    snprintf(response, response_size, "%s%s", title, text);

    struct MHD_Response *mhd_response;
    enum MHD_Result ret;

    if (strcmp(method, "GET") == 0 && strcmp(url, "/") == 0) {
        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                       (void *)response,
                                                       MHD_RESPMEM_MUST_FREE); // Free response after use
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
    } else {
        ret = MHD_NO;
    }

    return ret;
}
