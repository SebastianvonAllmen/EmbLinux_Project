#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "step_contoller.h"
#include "tcp_helper.h"

bool is_server = false;
const char* server_ip;
Choice own_choice, opponents_choice;

int startSteps(const bool cmd_is_server, const char* cmd_server_ip) {
    is_server = cmd_is_server;
    server_ip = cmd_server_ip;

    int ret_val = initStep();

    if (ret_val != 0) {
        return 1;
    }

    if (is_server) {
        ret_val = idleStep();

        if (ret_val != 0) {
            return 1;
        }
    } else {
        // TODO, pot check for null ip, but need to figure out where
        ret_val = searchStep(server_ip);

        if (ret_val != 0) {
            return 1;
        }
    }

    chooseStep(is_server);

    //waitStep();

    stopStep();

    return 0;
}

int initStep() {
    // Initialize TCP and start listening on port 8888
    int ret_val = initialize_tcp(8888);
    if (ret_val != 0) {
        return 1;
    }

    

    return 0;
}

int idleStep() {
    // Accept incoming connection
    puts("Waiting for incoming connections...");
    if (accept_connection() < 0) {
        return 1;
    }

    sendAndLog("Hello Client, I am ready to play!", true);
    
    return 0;
}


int searchStep(const char *server_ip) {
    if (connect_to_server(server_ip) != 0) {
        return 1;
    }  

    sendAndLog("Hello Server, I am ready to play!", true);

    // Buffer to store the response from the server
    char response[256];
    
    // Wait for a response from the server
    int ret_val = receive_message(response, sizeof(response));
    if (ret_val < 0) {
        puts("Error: Failed to receive message from server.");
        return 1;
    }

    // TODO change this to a define or something
    if (strcmp(response, "Hello Client, I am ready to play!") == 0) {
        puts("Received acknowledgment from server.");
    } else {
        puts("Unexpected response from server.");
        return 1;
    }

    return 0;
}

int chooseStep(bool is_server) {
    pthread_t response_thread;

    // Start the background thread to wait for a potential response
    if (pthread_create(&response_thread, NULL, waitForResponse, NULL) != 0) {
        puts("Error: Failed to create thread.");
        return 1;
    }

    // Simulate player choice
    if (is_server) {
        sleep(2);
        setOwnChoice(ROCK);
    } else {
        sleep(4);
        setOwnChoice(PAPER);
    }

    // Wait for the opponents response
    pthread_join(response_thread, NULL);

    return 0;
}

void* waitForResponse(void* arg) {
    char response[256];

    // Wait for a response from the other player
    int ret_val = receive_message(response, sizeof(response));
    if (ret_val < 0) {
        puts("Error: Failed to receive message from opponent.");
        pthread_exit(NULL);
    }

    // Convert the received string to an integer (enum)
    int received_choice = atoi(response);

    // Validate and set the opponent's choice
    if (received_choice >= ROCK && received_choice <= SCISSORS) {
        setOpChoice((Choice)received_choice);
        logChoice("Opponent's choice received:", (Choice)received_choice);
    } else {
        puts("Unexpected response from opponent.");
    }

    pthread_exit(NULL);
}

void setOwnChoice(Choice choice) {
    own_choice = choice;

    logChoice("Own choice set to", choice);

    // Send the enum value as an integer
    char message[10];
    snprintf(message, sizeof(message), "%d", choice); // Convert enum to string
    sendAndLog(message, false);
}


void setOpChoice(Choice choice) {
    opponents_choice = choice;

    logChoice("Opponent's choice set to", choice);
}

void logChoice(char* message, Choice choice) {
    char choice_str[10]; // Buffer to hold the choice as a string

    switch (choice) {
        case ROCK:
            strcpy(choice_str, "Rock");
            break;
        case PAPER:
            strcpy(choice_str, "Paper");
            break;
        case SCISSORS:
            strcpy(choice_str, "Scissors");
            break;
        default:
            strcpy(choice_str, "Unknown");
            break;
    }

    // Logging the message and choice
    printf("%s: %s\n", message, choice_str);
}

int stopStep() {
    // Close the client socket
    close_socket();

    return 0;
}