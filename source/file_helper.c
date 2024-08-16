#include "file_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool writeResultToFile(Choice own_choice, Choice opponents_choice) {
    FILE *file = fopen(RESULTS_FILE_PATH, "a"); // Open the file in append mode
    if (file == NULL) {
        perror("Failed to open file");
        return false;
    }

    long time_ms = get_current_time_ms(); // Get the current time in milliseconds

    // Write the result to the file in CSV format
    fprintf(file, "%ld,%d,%d,%s\n", time_ms, own_choice, opponents_choice, getResultString(own_choice, opponents_choice));

    fclose(file); // Close the file
    return true;
}

const char* getResultString(Choice own_choice, Choice opponents_choice) {
    if (opponents_choice == own_choice) {
        return "Draw";
    } else if ((own_choice == ROCK && opponents_choice == SCISSORS) ||
               (own_choice == PAPER && opponents_choice == ROCK) ||
               (own_choice == SCISSORS && opponents_choice == PAPER)) {
        return "Win";
    } else {
        return "Lose";
    }
}

long get_current_time_ms() {
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);

    long time_ms = spec.tv_sec * 1000 + spec.tv_nsec / 1000000; // Convert to milliseconds
    return time_ms;
}

char* readResultsFromFile() {
    FILE *file = fopen(RESULTS_FILE_PATH, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }


    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET); 

    char *content = (char *)malloc(file_size + 2); // +2 for the  \n and null terminator
    if (content == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\n';
    content[file_size + 1] = '\0';

    fclose(file);
    return content;
}
