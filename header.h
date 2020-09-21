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

char USER[1024], HOST[1024], CWD[2048], HOME[2048];
int positions;
long long int job_count;
pid_t CHILD_PID[1024];
char temp[100][1024];
char hist[20][1000];
int hist_i;

// main.c
void shell();
void prompt();
char *input();
void done();