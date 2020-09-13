#include "header.h"

void cd(char *line)
{
    char *token = line;
    int i=0;
    token = strtok(NULL, " \n\t\r");
    if(token == NULL) 
    {
        if(chdir(HOME) != 0) 
            perror("cd");
    }
    else {
        while (token != NULL)
        {
            if (strcmp(token, "~") == 0) {
                if (chdir(HOME) == -1){
                    perror("cd");
                }
            } else if (strcmp(token, "..") == 0) {
                if (chdir(dirname(CWD)) == -1)
                {
                    perror("cd");
                }
            } else {
                // char *new_dir = (char *)malloc(sizeof(char) * 2000);
                // strcpy(new_dir, CWD);
                // strcat(new_dir, token);
                if (chdir(token) == -1){
                    perror("cd");
                }
            }
            token = strtok(NULL, " \n\t\r");
            i++;
            if (i>1) {
                perror("only one argument expected");
                break;
            }
        }
    }
    // printf("\n");
    return;
}