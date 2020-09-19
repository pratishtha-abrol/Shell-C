#include "header.h"

char his[20][1024];

void add_to_history(char *line)
{
    // FILE *f;
    // char *com = NULL;
    strcpy(his[his_count], line);
    his_count++;
}

void print_history()
{
    for(int i=0; i<his_count; i++)
    {
        printf("%s\n", his[i]);
    }
}