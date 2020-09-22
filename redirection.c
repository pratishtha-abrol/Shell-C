#include "header.h"

void h_redirection(char **tokens, int *index, int fid, int attributes)
{
    if(*index == 0 || tokens[(*index) + 1] == NULL)
    {
        return;
    }
    tokens[*index] = NULL;
    int fileId = open(tokens[(*index) + 1], attributes, 0644);
    close(fid);
    dup(fileId);
    close(fileId);
    (*index)++;
}

void redirect(char *line)
{
    int i=0;
    char **tokens = malloc(sizeof(char *) * 100);
    char *token = line;
    token = strtok(NULL, " \"\n\t\r"); 
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
    }
    for(int j=0; j<i; j++)
    {
        if(!strcmp(tokens[j], ">")) {
            h_redirection(tokens, &j, 1, O_CREAT | O_WRONLY | O_TRUNC);
        }
        if(!strcmp(tokens[j], ">>")) {
            h_redirection(tokens, &j, 1, O_WRONLY | O_APPEND);
        }
        if(!strcmp(tokens[j], "<")) {
            h_redirection(tokens, &j, 0, O_RDONLY);
        }
    }
}