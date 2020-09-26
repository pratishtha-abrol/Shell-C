#include "header.h"
#include "echo.c"
#include "pwd.c"
#include "cd.c"
#include "ls.c"
#include "pinfo.c"
#include "history2.c"
#include "redirection.c"

int check_pipe (char *line)
{
    char *is_pipe = strstr(line, "|");
    if(is_pipe != NULL)
        return 1;

    else return 0;
}

int check_redirect (char *line)
{
    char *out = strstr(line, ">");
    char *in = strstr(line, "<");

    if((out != NULL) && (in != NULL))
        return 3;
    
    else if(out != NULL)
        return 2;
    
    else if(in != NULL)
        return 1;

    else return 0;
}

void execute (char *line)
{
    char *c = (char *)malloc(sizeof(char) *2000);
    strcpy(c, line);
    c = strtok(c, " \n\t\r");
    if(c == NULL)
    {
        return;
    }
    char **args = (char**)malloc(sizeof(char*) * 100);
    int n = 0;
    int background = 0;
    pid_t pid;
    
    while (c != NULL)
    {
        //printf("%s\n",com);
        args[n]  = (char *)malloc(sizeof(char) *strlen(c)+10);
        strcpy(args[n], c);
        c = strtok(NULL, " \n\t\r");
        n++;
    }

    if (!strcmp(args[n-1], "&"))
    {
        args[n-1] = NULL;
        background = 1;
        bg_count++;
    }
    else if(args[n-1][strlen(args[n-1]) -1] == '&')
    {
        args[n-1][strlen(args[n-1]) -1] = '\0';
        background = 1;
        bg_count++;
    }

    // if(check_pipe(line)) {
    //     pipe(line);
    // }
    if(check_redirect(line)) {
        redirect(line);
    }

    line = strtok(line, " \n\t\r");
    
    // redirect(line);

    if (strcmp(args[0], "echo") == 0) echo(line);
    else if (strcmp(args[0], "pwd") == 0) pwd(line);
    else if (strcmp(args[0], "cd") == 0) cd(line);
    else if (strcmp(args[0], "ls") == 0) ls(line);
    else if (strcmp(args[0], "history") == 0) history(line);
    else if (strcmp(args[0], "quit") == 0) {
        write_history();
        exit(0);
    }
    else if (strcmp(args[0], "pinfo") == 0) pinfo(line);
    else {
        pid = fork();
        args[n] = NULL;
        if (pid < 0) // Child process not created
        {
            perror("fork");
        }
        else if (pid == 0) // Child process
        {
            int fin, fout;
            setpgid(0, 0);
            execvp(args[0], args);
            perror("execvp");
            return;
        }
        else
        {
            if (background == 0)
            {
                wait(NULL);
                return;
            }
            else
            {
                CHILD_PID[bg_count] = pid;
                printf("Background process [%lld], pid : %i\n", bg_count, pid);
                strcpy(temp[bg_count], args[0]);
                return;
            }
            
        }                
    }
}