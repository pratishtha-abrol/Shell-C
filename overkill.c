#include "header.h"

void overkill()
{
    for (int i=0; i<job_count; i++)
    {
        kill(jobarray[i].PID, 9);
    }
    job_count = 0;
    bg_count = 0;
}