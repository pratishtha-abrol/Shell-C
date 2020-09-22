#include "header.h"
#include "execute.c"

int main()
{
    if (gethostname(HOST, sizeof(HOST)) == -1){
        perror("gethostname");
        exit(1);
    }
    if (getlogin_r(USER, sizeof(USER)) == -1) {
        perror("getlogin_r");
        exit(1);
    }
    if (getcwd(CWD, sizeof(CWD)) == NULL)
    {
        perror("current working directory not found");
        exit(1);
    }
    strcpy(HOME, CWD);
    load_history();
    // hist_i = 0;
    // counter = 0;
    // fd = open("history.txt", O_RDWR | O_CREAT, 0666);
    shell ();
}

void shell()
{
    char *line;

    do
    {
        signal(SIGCHLD, done);
        prompt();
        
        line = input();
        strcpy(hist[hist_i % 20], line);
        hist_i++;
        // add_to_history(line);
        // counter++;
        char *token = strtok(line, ";");
        char **cmd = malloc(256 * sizeof(char *));
        positions = 0;
        while (token != NULL) {
            cmd[positions++] = token;
            token = strtok(NULL, ";");
        }
        int i = 0;
        while (i<positions) {
            execute(cmd[i]);
            i++;
        }

        free(line);
        free(cmd);

    } while (1);
}

void prompt()
{
    // printf("> ");
    char *DIR;

    if (getcwd(CWD, sizeof(CWD)) == NULL)
    {
        perror("current working directory not found");
        exit(1);
    }
    else
    {
        int p;
        // strcpy(HOME, CWD);
        p = strcmp(CWD, HOME);
        // printf("%s %s\n", CWD, HOME);
        if(p == 0)
        {
            printf("\x1B[0m<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~\x1B[0m> ", USER, HOST);
        }
        else
        {
            DIR = CWD;
            printf("\x1B[0m<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~%s\x1B[0m> ", USER, HOST, DIR);
        }
    }
}

char *input ()
{
    char *line = NULL;
    ssize_t buff = 0;
    getline(&line, &buff, stdin);
    return line;
}

void done()
{
    int status;
    pid_t p;
    while (1) {
        p = waitpid(CHILD_PID[job_count], &status, WNOHANG);
        if (p == -1)
        {
            return;
        }
        else {
            if (WIFEXITED(status))
            {
                printf("\n[%lld]+\tDone\t%d\t%s\tExited Successfully\n", job_count, CHILD_PID[job_count], temp[job_count]);
                printf("Press Enter\n");
                // prompt();
                job_count--;
            }
        }
    }
}