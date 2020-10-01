#include "header.h"
#include "echo.c"
#include "pwd.c"
#include "cd.c"
#include "ls.c"
#include "pinfo.c"
#include "history2.c"
#include "redirection.c"
#include "pipeline.c"
#include "setenv.c"
#include "unsetenv.c"
#include "nightswatch.c"
#include "jobs.c"

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
        return 1;
    
    else if(out != NULL)
        return 2;
    
    else if(in != NULL)
        return 3;

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
    int n = 0, r, status;
    int background = 0;
    pid_t pid, wpid;
    
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

    if(check_pipe(line)) {
        pipeline(line);
        return;
    }
    if(r = check_redirect(line)) {
        redirect(line, r);
        return;
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
    else if (!strcmp(args[0], "setenv")) setenvironment(args, n);
    else if (!strcmp(args[0], "unsetenv")) unsetenvironment(args, n);
    else if (!strcmp(args[0], "nightswatch")) nightswatch(args, n);
    else if (!strcmp(args[0], "jobs")) jobs();
    else {
        pid = fork();
        args[n] = NULL;
        if (pid < 0) // Child process not created
        {
            perror("fork");
        }
        else if (pid == 0) // Child process
        {
            // int fin, fout;
            setpgid(0, 0);
            if(execvp(args[0], args) < 0)
            {
                perror("execvp");
                exit(1);
            }
        }
        else
        {
            if (background == 0)
            {
                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(STDIN_FILENO, pid);
                wpid = waitpid(pid, &status, WUNTRACED);
                tcsetpgrp(STDIN_FILENO, getpgrp());
                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
                if(WIFSTOPPED(status))
                {
                    strcpy(jobarray[job_count].job_name, line);
                    printf("%s with PID %d suspended\n", args[0], pid);
                    jobarray[job_count].PID = pid;
                    job_count++;
                }
                // return;
            }
            else
            {
                CHILD_PID[bg_count] = pid;
                
                strcpy(jobarray[job_count].job_name, line);
                jobarray[job_count].PID = pid;

                strcpy(temp[bg_count], jobarray[job_count].job_name);

                job_count++;

                printf("Background process [%lld], pid : %i\n", bg_count, pid);
                
                // return;
            }
        }                
    }
}