#include "headers.h"

void list_files(const char *target, const char *current_dir, int is_dir_only, int is_file_only, int execute_flag) {
    DIR *dir = opendir(current_dir);
    if (!dir) {
        perror("opendir");
        // exit(1);
        return ;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char entry_path[MAX_COMMAND_LENGTH];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", current_dir, entry->d_name);

        struct stat entry_info;
        if (lstat(entry_path, &entry_info) != 0) {
            perror("lstat");
            return;
        }

        if ((is_dir_only && S_ISDIR(entry_info.st_mode)) ||
            (is_file_only && S_ISREG(entry_info.st_mode)) ||
            (!is_dir_only && !is_file_only)) {

            if (strstr(entry->d_name, target) == entry->d_name) {
                // Print directories in blue and files in green using ANSI escape codes
                if (S_ISDIR(entry_info.st_mode)) {
                    printf("\033[1;34m%s/%s\033[0m\n", current_dir, entry->d_name); // Blue
                } else {
                    printf("\033[1;32m%s/%s\033[0m\n", current_dir, entry->d_name); // Green
                }

                if (execute_flag) {
                    if (S_ISDIR(entry_info.st_mode)) {
                        if (chdir(entry_path) != 0) {
                            perror("chdir");
                            exit(1);
                        }
                        printf("%s\n", entry_path);
                    } else {
                        FILE *file = fopen(entry_path, "r");
                        if (file) {
                            char line[256];
                            while (fgets(line, sizeof(line), file)) {
                                printf("%s", line);
                            }
                            fclose(file);
                        } else {
                            printf("Missing permissions for task!\n");
                        }
                    }
                }
            }
        }

        if (S_ISDIR(entry_info.st_mode)) {
            list_files(target, entry_path, is_dir_only, is_file_only, execute_flag);
        }
    }

    closedir(dir);
}
