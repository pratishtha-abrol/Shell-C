#include "header.h"

char **pipe_elements(char *line)
{
    char *p = strtok (line, "|");
    char **pipe_args = malloc(256 * sizeof(char *));

    int no = 0;

    while (p != NULL)
    {
        pipe_args[no++] = p;
        p = strtok (NULL, "|");
    }

    return pipe_args;
}

void pipeline(char *line)
{
    char **pipe_args = pipe_elements(line);
    int pipes[2], fd = 0;
    pid_t proc;

    for(int j=0; pipe_args[j]!= NULL; j++)
    {
        pipe(pipes);
        proc = fork();
        
        if(proc < 0) perror("pipe");
        
        else if(proc > 0)
        {
            wait(NULL);
            close(pipes[1]);
            fd = pipes[0];
        }

        else if(proc == 0)
        {
            dup2(fd , 0);
            
            if(pipe_args[j+1]!=NULL) 
                dup2(pipes[1],1);
            
            close(pipes[0]);
            execute(pipe_args[j]);
            exit(2);
        }
    }
    // prompt();
}