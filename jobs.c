#include "header.h"

void jobs()
{
    char *stat = malloc(sizeof(char) * 100);
    for (int i=0; i < job_count; i++)
    {
        sprintf(stat, "/proc/%d/status", jobarray[i].PID);
        FILE *f;
        if (!(f = fopen(stat, "r"))) 
            continue;
            // perror("job exited");
        else {
            char *info = find_line(stat, 3);
            char *temp = info;
            info = strtok(info, " :\n\t\r");
            info = strtok(NULL, " :\n\t\r");

            if(info[0] == 'T')
            {
                strcpy(info, "Stopped");
            }
            else
            {
                strcpy(info, "Running");
            }

            printf("[%d] %s %s [%d]\n", i+1, info, jobarray[i].job_name, jobarray[i].PID);
            free(temp);
        }  
    }
    free(stat);
}