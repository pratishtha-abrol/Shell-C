#include "header.h"

void kjob(char **args, int n)
{
    if (n != 3)
    {
        perror("Incorrect arguments");
        return;
    }
    else
    {
        int proc = atoi(args[1]);
        int sig = atoi(args[2]);
        if(proc > job_count)
        {
            perror("Job doesn't exist");
            return;
        }
        else 
        {
            kill(jobarray[proc-1].PID, sig);
        }
    }
    
}