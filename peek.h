#ifndef __PEEK_H
#define __PEEK_H

void get_permissions(mode_t mode, char *perms);
void peek_directory(char *directory_path,int show_details,int show_hidden);
#endif