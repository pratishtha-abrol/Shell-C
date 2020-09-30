#include "header.h"

void newborn(char **args, int n)
{
    while(1)
    {
        printf("feature not implemented");
        return;
    }
}

void interrupt(char **args, int n)
{
    FILE *foo = fopen("/proc/interrupts", "r");
    if(foo == NULL)
        printf("Can't open /proc/interrupts file\n");

    else
    {
        char *line = read_file("/proc/interrupts", 1);
        printf("%s\n",line);
        free(line);  
        fclose(foo);
    }

    while(1)
    {
        FILE *f = fopen("/proc/interrupts", "r");
        if(f == NULL)
            printf("Can't open /proc/interrupts file\n");

        else
        {
            char *line = read_file("/proc/interrupts", 3);
            for(int i=0; i < strlen(line); i++)
            {
                if(line[i]=='I')
                {
                    line[i] = '\0';
                    break;
                }
            }
            printf("%s\n",line);
            free(line);  
        }

        fclose(f);
        return;
    }
}

void nightswatch(char **args, int n)
{
    if(n != 4) {
        perror("Expected command in form of 'nightswatch -n [seconds] [newborn/interrupt]'");
        return;
    }

    int in = !(strcmp(args[3], "interrupt"));
    int new = !(strcmp(args[3], "newborn"));

    if(in)
    {
        interrupt(args, n);
    }
    else if (new)
    {
        newborn(args, n);
    }
}