#ifndef TCP_HELPER_H
#define TCP_HELPER_H

#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

// Function declarations
int initialize_tcp(int port);
int accept_connection();
void set_client_socket(int socket);
void sendToClientAndLog(const char *message);
int receive_message(char *buffer, int buffer_size);
void close_client_socket();

#endif // TCP_HELPER_H
