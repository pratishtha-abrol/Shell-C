#include "header.h"

int isfile(char* path) 
{
    struct stat f;
    if(stat(path, &f) == 0 && !S_ISDIR(f.st_mode))
        return 1;
    else return 0;
}

void redirect(char *line)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    int status;

    char *output[2], *input[2];
    char * out_file = NULL;
    char * in_file = NULL;

    char * inp = strstr(line, "<");
    int in = !(inp == NULL);
    int out_type = 0;
    char * out = strstr(line, ">>");
    
    if(out != NULL)
        out_type = 2;

    else 
    {
        out = strstr(line, ">");
        if(out != NULL)
            out_type = 1;
    }

    output[0] = &line[0];

    if(out_type)
    { 
        output[0] = strtok(line, ">");
        output[1] = strtok(NULL, ">");
        out_file = strtok(output[1], " \r\t\n");
    }

    input[0] = output[0];
    if(in)
    { 
        input[0] = strtok(input[0], "<");
        input[1] = strtok(NULL, "<");
    }

    char **args = (char**)malloc(sizeof(char*) * 300);
    int n = 0;
    
    if(in)
    {
        if(input[1] == NULL)
        {
            printf("Specify file name for input\n");
            return;
        }
        
        //printf("\n fk no %s\n",input[1]);
        in_file = strtok(input[1], " \n\r\t");
        if(!isfile(in_file))
        {
            printf("File does not exist\n");
            return;
        }
    
    }

    input[0] = strtok(input[0], " \n\r\t");

    while (input[0] != NULL)
    {
        args[n]  = (char *)malloc(sizeof(char) *strlen(input[0])+10);
        strcpy(args[n], input[0]);
        input[0] = strtok(NULL, " \n\t\r");
        n++;
    }

    args[n] = NULL;

    if(out_type)
    {
        if(out_file == NULL)
        {
            printf("Enter output file\n");
            return;
        }

        //printf("%s %d\n", out_file, out_type);
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("Error in forking");
        return;
    }

    if(pid == 0)
    {
        if(in)
        {
            int fd_in = open(in_file, O_RDONLY);
            if(fd_in < 0) 
            {
                perror("Input redirection");
                return;
            }   
            
            dup2(fd_in, 0);
            close(fd_in);
        }

        if(out_type)
        {
            int fd_out;
            if(out_type == 1)
                fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            else if(out_type == 2)
                fd_out = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if(fd_out < 0)
            {
                perror("Output Redirection");
                return;
            }
            
            dup2(fd_out, 1);         
            close(fd_out);
        }
        
        if (execvp(args[0], args) < 0) 
        {     
            perror("line not found");
            exit(EXIT_FAILURE);
        }
        
        dup2(saved_stdin, 0);
        close(saved_stdin);
        
        dup2(saved_stdout, 1);
        close(saved_stdout);
    }        
    
    else while (wait(&status) != pid);

    for(int j=0; j < n; j++)
        free(args[j]);
    free(args);
}