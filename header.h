#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/select.h>

char USER[1024], HOST[1024], CWD[2048], HOME[2048];
int positions, job_count;
long long int bg_count;
pid_t SHELL_ID, CHILD_PID[1024];
char temp[100][1024];
char hist[20][1000];
int hist_i;

struct job
{
    char job_name[500];
    pid_t PID;
};

typedef struct job job;
job jobarray[100];
job current_fg;

// main.c
void shell();
void prompt();
char *input();
void done();
void ctrl_c (int signum);
void ctrl_z (int signum);
char * find_line(char *filename, int n);
void del_process(int id);

// execute.c
void execute (char *line);

#endif