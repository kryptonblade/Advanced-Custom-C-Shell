#include "headers.h"

int main()
{
    char *home_directory = currentdirectory();
    char *prev_directory = currentdirectory();
    char *cwd = (char *)malloc(sizeof(char) * (4096));
    char *h = (char *)malloc(sizeof(char) * (4096));
    char *H = (char *)malloc(sizeof(char) * (4096));
    char *K = (char *)malloc(sizeof(char) * (4096));
    char *input = (char *)malloc(sizeof(char) * (4096));
    char *curr_dir_bfr_warp = (char *)malloc(sizeof(char) * (4096));
    char *new_directory=(char *)malloc(sizeof(char)*4096);
    char *wanted_directory=(char *)malloc(sizeof(char)*4096);
    char* search=(char *)malloc(sizeof(char)*4096);
    char* target_directory=(char *)malloc(sizeof(char)*4096);
    initialize_history();
    load_history_from_file();
    while (1)
    {
        prompt(home_directory);
        char INPUT[4096];
        fgets(INPUT, 4096, stdin);
        INPUT[strlen(INPUT) - 1] = '\0';
        // input[strcspn(input, "\n")] = '\0';
        if(strlen(INPUT) == 0)
            continue;
        char* ans = INPUT;
        char* semicolon = ";";
        char* H = strtok_r(ans,semicolon,&ans);
        int count=0;int flag=0;
        while(H!=NULL)
        {
            strcpy(h,H);
            strcpy(input,H);
            if (strcmp(input,"pastevents") == 0) {
            print_history();
            flag=1;
            H = strtok_r(ans,semicolon,&ans);
            continue;
        } else if (strcmp(input, "pastevents purge") == 0) {
            purge_history();
            save_history_to_file();
            flag=1;
            H = strtok_r(ans,semicolon,&ans);
            continue;
        } else if (strstr(input, "pastevents execute") == input) {
            int index;
            if (sscanf(input, "pastevents execute %d", &index) == 1) {
                execute_history(index,h);
            } else {
                printf("Invalid 'pastevents execute' command format.\n");
            }
        }
        if(strcmp(input,h)!=0)
        strcpy(input,h);
        char* delim=" \n"; 
        char *token = strtok(input, delim);
        if(strcmp(token,"warp")==0)
        {
            token = strtok(NULL, delim);
        while (token != NULL) {
            cwd=getcwd(cwd, 4096);
            strcpy(curr_dir_bfr_warp,cwd);
            warp(cwd, token, home_directory,prev_directory);
            strcpy(prev_directory,curr_dir_bfr_warp);
            token = strtok(NULL, delim);
        }
        }
        else if(strcmp(token,"peek")==0)
        {
            token=strtok(NULL,delim);
            int show_contents=0;
            int show_hidden=0;

            while(token!=NULL)
            {
                if(strcmp(token,"-l")==0)
                {
                    show_contents=1;
                }   
                else if(strcmp(token,"-a")==0)
                {
                    show_hidden=1;
                }
                else if((strcmp(token,"-al")==0)||(strcmp(token,"-la")==0))
                {
                    show_contents=1;
                    show_hidden=1;
                }
                else
                {
                    strcpy(wanted_directory,token);
                }
                token = strtok(NULL, delim);
            }
            if(strlen(wanted_directory)==0)
            {
                cwd=currentdirectory();
                strcpy(wanted_directory,cwd);
            }
            if(strcmp(wanted_directory,"~")==0)
            {
                strcpy(wanted_directory,home_directory);
            }
            peek_directory(wanted_directory,show_contents,show_hidden);
        }
        else if(strcmp(token,"proclore")==0)
        {
            token=strtok(NULL,delim);
            if(token==NULL)
            {
                char self_pid[10];
                snprintf(self_pid, sizeof(self_pid), "%d", getpid());
                print_process_info(self_pid);
            }
            else
            {
                // printf("%d\n",index1);
                print_process_info(token);
            }
        }
        else if(strcmp(token,"seek")==0)
        {
            int d_flag=0;
            int f_flag=0;
            int e_flag=0;int ss=0;
            token=strtok(NULL,delim);
            while(token!=NULL)
            {
                if(strcmp(token,"-d")==0)
                {
                    d_flag=1;
                }
                else if(strcmp(token,"-f")==0)
                {
                    f_flag=1;
                }
                else if(strcmp(token,"-e")==0)
                {
                    e_flag=1;
                }
                else if(ss==0)
                {
                    strcpy(search,token);
                    ss++;
                }
                else
                {
                    strcpy(target_directory,token);
                }
                token=strtok(NULL,delim);
            }
            if(strlen(target_directory)<2)
            {
                char* cur_dir=currentdirectory();
                strcpy(target_directory,cur_dir);
            }
            list_files(search, target_directory,d_flag,f_flag,e_flag);
        }
        else if (strcmp(input, "exit") == 0) {
            exit(1);
        } else {
            time_t start = time(NULL);
            execute_foreground(input);
            time_t end = time(NULL);
            double time_taken = difftime(end, start);
            if (time_taken > 2) {
                printf("%s : %.0fs\n", input, time_taken);
            }
        }
        if(count==0)
        {
            strcpy(K,h);
            count++;
        }
        else{
            strcat(K,semicolon);
            strcat(K,h);
        }
        H = strtok_r(ans,semicolon,&ans);
        }
        if(flag==0)
        {add_to_history(K);
        save_history_to_file();}
    }
    free_history();
    return 0;
}