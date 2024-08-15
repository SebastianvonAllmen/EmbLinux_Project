#ifndef STEP_CONTROLLER_H
#define STEP_CONTROLLER_H

#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

typedef enum {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2
} Choice;


int startSteps(const bool cmd_is_server, const char* cmd_server_ip);
int initStep();
int idleStep();
int searchStep(const char* ipAdress);
int chooseStep(bool is_server);
Choice getRandomChoice();
void* waitForResponse(void* arg);
void setOwnChoice(Choice choice);
void setOpChoice(Choice choice);
void logChoice(char* message, Choice choice);
const char* enumChoiceToString(Choice choice);
int resultStep();
int stopStep();

#endif // STEP_CONTROLLER_H