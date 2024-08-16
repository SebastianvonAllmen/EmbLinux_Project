#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stdbool.h>

#include "step_contoller.h"

#define RESULTS_FILE_PATH "../log/results.csv"

bool writeResultToFile(Choice own_choice, Choice opponents_choice);
const char* getResultString(Choice own_choice, Choice opponents_choice);
long get_current_time_ms();
char* readResultsFromFile();

#endif // FILE_HELPER_H
