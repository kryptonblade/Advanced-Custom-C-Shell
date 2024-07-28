#include "headers.h"

void print_process_info(const char *pid_str) {
    int pid = atoi(pid_str); // Convert PID string to integer
    
    // Construct the file paths for process information
    char stat_file_path[100];
    char exe_file_path[100];
    snprintf(stat_file_path, sizeof(stat_file_path), "/proc/%d/stat", pid);
    snprintf(exe_file_path, sizeof(exe_file_path), "/proc/%d/exe", pid);
    
    // Open the /proc/<pid>/stat file for reading
    FILE *stat_file = fopen(stat_file_path, "r");
    if (stat_file == NULL) {
        perror("Error opening stat file");
        return;
    }
    
    // Read process status from stat file
    int pid_read;
    char status;
    int pgrp;
    long unsigned int vm;
    fscanf(stat_file, "%d %*s %c %d %*s %*s %*s %*s %*s %*s %lu", &pid_read, &status, &pgrp, &vm);
    fclose(stat_file);
    
    // Open the /proc/<pid>/exe file to read the executable path
    char exe_path[4096];
    ssize_t exe_path_length = readlink(exe_file_path, exe_path, sizeof(exe_path) - 1);
    if (exe_path_length == -1) {
        perror("Error reading exe path");
        return;
    }
    exe_path[exe_path_length] = '\0';
    char process_status[20];
    if (status == 'R' || status == 'D') {
        snprintf(process_status, sizeof(process_status), "R");
    } else if (status == 'T' || status == 't') {
        snprintf(process_status, sizeof(process_status), "R+");
    } else if (status == 'S' || status == 's') {
        snprintf(process_status, sizeof(process_status), "S");
    } else if (status=='+'){
        snprintf(process_status, sizeof(process_status), "S+");
    } else if (status == 'Z') {
        snprintf(process_status, sizeof(process_status), "Z");
    } else {
        snprintf(process_status, sizeof(process_status), "Unknown");
    }
    
    // Print the process information
    printf("pid : %d\n", pid);
    printf("process status : %s\n", process_status);
    printf("Process Group : %d\n", pgrp);
    printf("Virtual memory : %lu\n", vm);
    printf("executable path : %s\n", exe_path);
}