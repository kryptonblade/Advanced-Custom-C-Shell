#include "headers.h"

char *username()
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (pw != NULL)
    {
        // printf("Username: %s\n", pw->pw_name);
        return pw->pw_name;
    }
    else
    {
        // perror("Error getting username");
        return NULL;
    }
}

char *currentdirectory()
{
    char *p = (char *)malloc(sizeof(char) * (4096));
    p = getcwd(p, 4096);
    return p;
}

void prompt(char* home_directory) {
    // Do not hardcode the prompt
    char *user = username();
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        perror("Error getting system name");
    }
    char *current_directory = currentdirectory();
        int l = strlen(home_directory);
        int r = strlen(current_directory);
        if (l <= r)
        {
            for (int i = 0; i < l; i++)
            {
                if (current_directory[i] != home_directory[i])
                {
                    l = -1;
                    break;
                }
            }
            if (l == -1)
            {
                printf("<%s@%s:%s>", user, hostname, current_directory);
            }
            else
            {
                if (l == r)
                {
                    printf("<%s@%s:~>", user, hostname);
                }
                else
                {
                    char *s=(char *)malloc(sizeof(char) * (4096));
                    s[0]='~';
                    for(int i=l;i<r;i++)
                    {
                        s[i-l+1]=current_directory[i];
                    }
                    printf("<%s@%s:%s>", user, hostname, s);
                }
            }
        }
        else
        {
            printf("<%s@%s:%s>", user, hostname, current_directory);
        }  
}
