#include "header.h"
#include "echo.c"
#include "pwd.c"
#include "cd.c"
#include "ls.c"
#include "pinfo.c"

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
    int n = 0, background = 0;
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
        job_count++;
    }

    line = strtok(line, " \n\t\r");
    if (strcmp(line, "echo") == 0) echo(line);
    else if (strcmp(line, "pwd") == 0) pwd(line);
    else if (strcmp(line, "cd") == 0) cd(line);
    else if (strcmp(line, "ls") == 0) ls(line);
    else if (strcmp(line, "quit") == 0) {
        // writehistory();
        exit(0);
    }
    else if (strcmp(line, "pinfo") == 0) pinfo(line);
    else {
        pid = fork();
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
            exit(1);
        }
        else
        {
            if (!background)
            {
                wait(NULL);
            }
        }                
    }
}