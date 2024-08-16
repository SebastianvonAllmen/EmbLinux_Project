#ifndef STEP_CONTROLLER_H
#define STEP_CONTROLLER_H

#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define TCP_PORT 8888
#define LIS3DH_ADDR 0x18   // I2C address of the LIS3DH
#define MAXPLAYCOUNT 3   // I2C address of the LIS3DH

typedef enum {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2,
    FOUNTAIN = 3
} Choice;


int startSteps(const bool cmd_is_server, const char* cmd_server_ip);
int initStep();
int idleStep();
int searchStep(const char* ipAdress);
int chooseStep(bool is_server);
Choice getRandomChoice();
Choice getRandomSleepTime(int maxTime);
void* waitForResponse(void* arg);
void setOwnChoice(Choice choice);
void setOpChoice(Choice choice);
void logChoice(char* message, Choice choice);
const char* enumChoiceToString(Choice choice);
int resultStep();
int stopStep();
void countdownPlay();

#endif // STEP_CONTROLLER_H