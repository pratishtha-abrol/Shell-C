#include "header.h"

void setenvironment(char **args, int n)
{
    if (n == 0) perror("Argument expected");
    else if (n > 3) perror("Only 1 or 2 arguments expected");
    else if (n == 2)
    {
        if(setenv(args[1], "\0", 2) < 0)
            perror("setenv");
    }
    else if (n == 3)
    {
        if(setenv(args[1], args[2], 2) < 0)
            perror("setenv");
    }
    return;
}
