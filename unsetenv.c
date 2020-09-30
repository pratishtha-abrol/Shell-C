#include "header.h"

void unsetenvironment(char **args, int n)
{
    if (n == 0) perror("Argument expected");
    else if (n > 2) perror("Only 1 argument expected");
    else if (n == 2)
    {
        if(unsetenv(args[1]) < 0)
            perror("unsetenv");
    }
    return;
}