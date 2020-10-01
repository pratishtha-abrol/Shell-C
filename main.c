#include "header.h"
#include "execute.c"

int main()
{
    SHELL_ID = getpid();
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
    job_count = 0;
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
        current_fg.PID = -1;
        signal(SIGCHLD, done);
        signal(SIGINT, ctrl_c);
        signal(SIGTSTP, ctrl_z);
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
        p = waitpid(CHILD_PID[bg_count], &status, WNOHANG);
        if (p == -1)
        {
            return;
        }
        else {
            if (WIFEXITED(status))
            {
                printf("\n[%lld]+\tDone\t%d\t%s\tExited Successfully\n", bg_count, CHILD_PID[bg_count], temp[bg_count]);
                printf("Press Enter\n");
                // prompt();
                bg_count--;
            }
        }
    }
}

void ctrl_c (int signum)
{
    pid_t p = getpid();
    if (p != SHELL_ID) return;
    if( p == SHELL_ID && current_fg.PID == -1)
    {
        prompt();
        fflush(stdout);
    }
    if (current_fg.PID != -1)
    {
        kill(current_fg.PID, SIGINT);
    }
    signal(SIGINT, ctrl_c);
}

void ctrl_z (int signum)
{
    pid_t p = getpid();
    if (p != SHELL_ID) return;
    if (current_fg.PID != -1)
    {
        kill(current_fg.PID, SIGTTIN);
        kill(current_fg.PID, SIGTSTP);
        jobarray[job_count].PID = current_fg.PID;
        strcpy(jobarray[job_count].job_name, current_fg.job_name);
        job_count++;
    }
    signal(SIGTSTP, ctrl_z);
    if(p == SHELL_ID)
    {
        prompt();
        fflush(stdout);
    }
    return;
}

char * find_line(char *filename, int n)
{
    FILE* file = fopen(filename, "r");
    char line[256];
    char *info = malloc(sizeof(char) *256);
    int i = 0;
    while (fgets(line, sizeof(line), file)) 
    {
        i++;
        if(i == n)
            strcpy(info, line);
    }

    fclose(file);
    return info;
}

void del_process(int id)
{
    if (id == -1) job_count = 0;
    else
    {
        for (int i=0; i<job_count; i++)
        {
            if (jobarray[i].PID == id)
            {
                for (int j = i; j<job_count-1; j++)
                {
                    jobarray[j] = jobarray[j+1];
                }
                job_count--;
            }
        }
    }
}