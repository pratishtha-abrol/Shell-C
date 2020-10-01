#include "header.h"

void bg(char **args, int n)
{
    if (n != 2)
    {
        perror("Incorrect number of arguments");
        return;
    }
    int num = atoi(args[1]);
    if (num > job_count)
    {
        perror("No such job exists");
        return;
    }
    kill(jobarray[num].PID, SIGTTIN);
    kill(jobarray[num].PID, SIGCONT);
}