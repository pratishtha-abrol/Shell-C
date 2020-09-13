#include "header.h"

void echo(char *line)
{
    char *token = line;
    token = strtok(NULL, " \"\n\t\r"); 
    while (token != NULL)
    {
        printf("%s ",token);
        token = strtok(NULL, " \"\n\t\r");
    }
    printf("\n");
    return;
}