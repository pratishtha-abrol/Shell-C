#include "header.h"

void pwd(char *line)
{
    char *token = line;
    token = strtok(NULL, " \"\n\t\r"); 
    if (token != NULL) 
    {
        perror("can't use parameters");
        return;
    }
    char *buff = (char *)malloc(sizeof(char) * 10000);
    buff = getcwd(NULL, 0);
    printf("%s", buff);
    printf("\n");
    return;
}