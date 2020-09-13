#include "header.h"

void pinfo(char *line)
{
    char *token = line;
    token = strtok(NULL, "\"\n\t\r");
    pid_t pid;
    
    if(token == NULL)
        pid = getpid();

    else
        pid = atoi(token);

    char *status = (char *)malloc(sizeof(char) * 100);
    char *exe = (char *)malloc(sizeof(char) * 100);

    sprintf(status, "/proc/%d/status", pid);
    sprintf(exe, "/proc/%d/exe", pid);

    FILE *file;
    if (!(file = fopen(status, "r")))
    {
        printf("The process with pid %d doesn't exist.\n", pid);
    }
    else
    {
        char i[1024];
        char *info1 = (char *)malloc(sizeof(char) * 1000);
        char *info2 = (char *)malloc(sizeof(char) * 1000);
        int j = 0;
        while (fgets(i, sizeof(i), file)) 
        {
            j++;
            if(j == 3)
                strcpy(info1, i);
            if(j == 18)
                strcpy(info2, i);
        }
        fclose(file);
        char *s = strtok(info1, ":\t\r ");
        s = strtok(NULL, ":\t\r ");
        char *m = strtok(info2, ":\t\r ");
        m = strtok(NULL, ":\t\r ");
        printf("pid -- %d\nProcess Status -- %s\nVirtual Memory -- %s\nExecutable Path -- ", pid, s, m);
        char path[2048];
        char *ptr;
        if (readlink(exe, path, 1000) < 0)
        {
            printf("N/A\n");
        }
        else
        {
            strcat(path, "\0");
            ptr = strstr(path, HOME);
            if(ptr)
            {
                ptr += strlen(HOME);
                printf("~%s\n", ptr);
            }
            else
            {
                printf("%s\n", path);
            }
        }
    }  
    free(status);
    free(exe);  
}