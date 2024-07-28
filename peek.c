#include "headers.h"

void get_permissions(mode_t mode, char *perms) {
    strcpy(perms, "----------");
    if (S_ISDIR(mode))  perms[0] = 'd';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
}

void peek_directory(char *directory_path,int show_details,int show_hidden)
{
    struct dirent **entry_list;
    int num_entries = scandir(directory_path, &entry_list, NULL, alphasort);

    if (num_entries < 0) {
        perror("Error opening directory");
        return;
    }
    if((show_details==0))
    {
        
        for (int i = 0; i < num_entries; i++) {
        struct dirent *entry = entry_list[i];

        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }
            else
            {
                struct stat file_info;
                char file_path[4096];
                snprintf(file_path, sizeof(file_path), "%s/%s", directory_path, entry->d_name);
                if (lstat(file_path, &file_info) == -1) {
                 perror("Error getting file info");
                continue;
                }
                if(S_ISDIR(file_info.st_mode))
                {
                    printf("\033[34m%s\033[0m ",entry->d_name);
                }
                else if(file_info.st_mode & S_IXUSR || file_info.st_mode & S_IXGRP || file_info.st_mode & S_IXOTH)
                {
                    printf("\033[32m%s\033[0m ",entry->d_name);
                }
                else
                {
                    printf("%s ",entry->d_name);
                }
            }
        }
        printf("\n");
    }
    else if((show_details!=0))
    {  
        for (int i = 0; i < num_entries; i++) {
        struct dirent *entry = entry_list[i];

        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }
            else
            {
                struct stat file_info;
                char file_path[4096];
                snprintf(file_path, sizeof(file_path), "%s/%s", directory_path, entry->d_name);
                if (lstat(file_path, &file_info) == -1) {
                 perror("Error getting file info");
                continue;
                }
            char perms[11];
            get_permissions(file_info.st_mode, perms);
            struct passwd *pwd = getpwuid(file_info.st_uid);
            struct group *grp = getgrgid(file_info.st_gid);
            char time_str[80];
            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_info.st_mtime));
            // printf("%s %3ld %s %s %8ld %s %s\n", perms, file_info.st_nlink, pwd->pw_name, grp->gr_name,
            //        file_info.st_size, time_str, entry->d_name);
            if(S_ISDIR(file_info.st_mode))
            {
                printf("%s %3ld %s %s %8ld %s \033[34m%s\033[0m\n", perms, file_info.st_nlink, pwd->pw_name, grp->gr_name,
                   file_info.st_size, time_str, entry->d_name);
            }
            else if (file_info.st_mode & S_IXUSR || file_info.st_mode & S_IXGRP || file_info.st_mode & S_IXOTH)
            {    
                printf("%s %3ld %s %s %8ld %s \033[32m%s\033[0m\n", perms, file_info.st_nlink, pwd->pw_name, grp->gr_name,
                   file_info.st_size, time_str, entry->d_name);
            }
            else
            {
                printf("%s %3ld %s %s %8ld %s %s\n", perms, file_info.st_nlink, pwd->pw_name, grp->gr_name,
                   file_info.st_size, time_str, entry->d_name);
            }
            }
            }
    }
}