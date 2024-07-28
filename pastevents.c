#include "headers.h"



char **history; 

void initialize_history() {
    history = (char **)malloc(MAX_HISTORY_SIZE * sizeof(char *));
    for (int i = 0; i < MAX_HISTORY_SIZE; i++) {
        history[i] = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
        history[i][0] = '\0';
    }
}

void load_history_from_file() {
    const char* file_path2="/history.txt";
    char *file_path = (char *)malloc(sizeof(char) * (4096));
    file_path = getcwd(file_path, 4096);
    strcat(file_path,file_path2);
    FILE *file = fopen(file_path, "r+");
    if (file) {
        char line[MAX_COMMAND_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            if( line[strlen(line) - 1]=='\n')
            line[strlen(line) - 1] = '\0'; 
            add_to_history(line);
        }
        fclose(file);
    }
}

void save_history_to_file() {
    const char* file_path2="/history.txt";
    char *file_path = (char *)malloc(sizeof(char) * (4096));
    file_path = getcwd(file_path, 4096);
    strcat(file_path,file_path2);
    FILE *file = fopen(file_path,"w+");
    if (file) {
        for (int i = 0; i < history_count; i++) {
        if (fprintf(file,"%s\n",history[i]) != EOF) {
        } else {
        perror("Error writing string");
        }
        }
        fclose(file);
    }
}

void add_to_history(const char *command) {

    if (history_count==0 ||strcmp(history[history_count - 1], command) != 0) {
        if (history_count == MAX_HISTORY_SIZE) {
            for (int i = 0; i < history_count - 1; i++) {
                strcpy(history[i], history[i + 1]);
            }
            history_count--;
        }
        strcpy(history[history_count], command);
        history_count++;
    }
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%s\n", history[i]);
    }
}

void purge_history() {
    history_count = 0;
}

void execute_history(int index,char* input) {
    if (index >= 0 && index <= history_count) {
        strcpy(input,history[history_count-index]);
    }
}

void free_history() {
    for (int i = 0; i < MAX_HISTORY_SIZE; i++) {
        free(history[i]);
    }
    free(history);
}
