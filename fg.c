#include "header.h"

void fg(char **args, int n)
{
    if(n != 2)
    {
        perror("Incorrect number of arguments");
        return;
    }
    int num = atoi(args[1]);
    if (num > job_count)
    {
        perror("Job doesn't exist");
        return;
    }
    int pid = jobarray[num].PID;
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU,SIG_IGN);
    tcsetpgrp(STDIN_FILENO,pid);
    current_fg.PID = pid;
    strcpy(current_fg.job_name,jobarray[num].job_name);
    kill(pid, SIGCONT);
    del_process(pid);
    waitpid(-1, NULL, WUNTRACED);
    tcsetpgrp(STDIN_FILENO,getpgrp());
    signal(SIGTTIN,SIG_DFL);
    signal(SIGTTOU,SIG_DFL);
}