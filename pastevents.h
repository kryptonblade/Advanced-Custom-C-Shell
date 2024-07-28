#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H
#define MAX_HISTORY_SIZE 15
#define MAX_COMMAND_LENGTH 4096
#define HISTORY_FILE "history.txt"

void add_to_history(const char *command);
void initialize_history();
void load_history_from_file();
void save_history_to_file();
void add_to_history(const char *command);
void print_history() ;
void purge_history();
void execute_history(int index,char* h);
void free_history();

#endif