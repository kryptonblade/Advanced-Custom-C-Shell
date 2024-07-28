#include "headers.h"


void warp(char *current_directory, char *destination,char *home_directory,char *prev_directory) {
    char new_directory[4096];
    if (destination[0] == '~') {
        strcpy(new_directory, home_directory);
        strcat(new_directory, destination + 1); // Skip the '~' character
    } else if (strcmp(destination, ".") == 0) {
        strcpy(new_directory, current_directory);
    } else if (strcmp(destination, "..") == 0) {
        char *last_slash = strrchr(current_directory, '/');
        if (last_slash != NULL) {
            *last_slash = '\0';
        }
        strcpy(new_directory, current_directory);
    } else if (strcmp(destination, "-") == 0) {
        strcpy(new_directory, prev_directory);
} else {
        strcpy(new_directory, destination);
    }
    new_directory[strlen(new_directory)] = '\0';
    if (chdir(new_directory) == 0) {
        getcwd(new_directory, 4096);
        printf("%s\n", new_directory);
    } else {
        perror("Error changing directory");
    }
}