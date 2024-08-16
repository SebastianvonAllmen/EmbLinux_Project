#ifndef REST_CONTROLLER_H
#define REST_CONTROLLER_H

#include <microhttpd.h>

void *start_rest_api(void *arg);
void stop_rest_api(void);
enum MHD_Result answer_to_connection(void *cls, struct MHD_Connection *connection,
                                     const char *url, const char *method,
                                     const char *version, const char *upload_data,
                                     size_t *upload_data_size, void **con_cls);

#endif // REST_CONTROLLER_H
