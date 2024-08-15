#ifndef STEP_CONTROLLER_H
#define STEP_CONTROLLER_H

#include <stdbool.h>
#include <unistd.h>

int startSteps(const bool cmd_is_server, const char* cmd_server_ip);
int initStep();
int idleStep();
int searchStep(const char* ipAdress);
int chooseStep(bool is_server);
int stopStep();

#endif // STEP_CONTROLLER_H