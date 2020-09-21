#include "header.h"

void long_ls(char *file, int flag)
{
    DIR* dir = opendir(file);
    struct dirent* c;
    if(dir) {
        struct stat name;
        if (stat(file, &name) == -1) {
        perror("long_ls");
        }
        else {
            while((c = readdir(dir)) != NULL) {
                struct stat p;
                if(!stat(c->d_name, &p)) {
                    if (flag == 1) 
                    {
                        // struct stat name;
                        // if (stat(file, &name) == -1) {
                        //     perror("long_ls");
                        // }
                        printf((p.st_mode & S_IFDIR)? "d":"-");
                        printf((p.st_mode & S_IRUSR)? "r":"-");
                        printf((p.st_mode & S_IWUSR)? "w":"-");
                        printf((p.st_mode & S_IXUSR)? "x":"-");
                        printf((p.st_mode & S_IRGRP)? "r":"-");
                        printf((p.st_mode & S_IWGRP)? "w":"-");
                        printf((p.st_mode & S_IXGRP)? "x":"-");
                        printf((p.st_mode & S_IROTH)? "r":"-");
                        printf((p.st_mode & S_IWOTH)? "w":"-");
                        printf((p.st_mode & S_IXOTH)? "x":"-");
                        printf("\t");
                        printf("%ld", p.st_size);
                        printf("\t");
                        printf("%s\t", ctime(&p.st_atime));
                        printf("%s\n", c->d_name);
                    }
                    else {
                        if(c->d_name[0] != '.') 
                        {
                            // struct stat name;
                            // if (stat(file, &name) == -1) {
                            //     perror("long_ls");
                            // }
                            printf((p.st_mode & S_IFDIR)? "d":"-");
                            printf((p.st_mode & S_IRUSR)? "r":"-");
                            printf((p.st_mode & S_IWUSR)? "w":"-");
                            printf((p.st_mode & S_IXUSR)? "x":"-");
                            printf((p.st_mode & S_IRGRP)? "r":"-");
                            printf((p.st_mode & S_IWGRP)? "w":"-");
                            printf((p.st_mode & S_IXGRP)? "x":"-");
                            printf((p.st_mode & S_IROTH)? "r":"-");
                            printf((p.st_mode & S_IWOTH)? "w":"-");
                            printf((p.st_mode & S_IXOTH)? "x":"-");
                            printf("\t");
                            printf("%ld", p.st_size);
                            printf("\t");
                            printf("%s\t", ctime(&p.st_atime));
                            printf("%s\n", c->d_name);
                        }
                    }
                }
            }
        }
    }
    else {
        perror("directory not found");
    }
}

void norm_ls(char *file, int flag)
{
    DIR* dir = opendir(file);
    struct dirent* c;
    if(dir) {
        while((c = readdir(dir)) != NULL) {
            if (flag == 1) printf("%s\n",c->d_name);
            else {
                if(c->d_name[0] != '.') 
                printf("%s\n",c->d_name);
            }
        }
    }
    else {
        perror("directory not found");
    }
}

void ls (char *line)
{
    char *token = line;
    int hidden = 0, ll = 0, dir = 0, dir2 = 0, i=0, j=0;
    char **n_dir = malloc(sizeof(char *) * 20000);
    n_dir[i] = CWD;
    // hidden = 1 -> display hidden
    // all = 1 -> use long display
    // dir = 0 -> pwd, dir = -1 -> dirname(pwd), dir = 1 -> home, dir = 2 -> accept directory name
    token = strtok(NULL, " \"\n\t\r");
    if (token == NULL)
    {
        hidden = 0; ll = 0; dir = 0;
    }
    else
    {
        while (token != NULL)
        {
            // if (strcmp(token, ".") == 0) {
            //     dir = 0;
            //     n_dir[i++] = CWD;
            // }
            // else if (strcmp(token, "..") == 0) {
            //     dir = -1;
            //     n_dir[i++] = dirname(CWD);
            // }
            if (strcmp(token, "~") == 0) {
                dir = 1;
                n_dir[i++] = HOME;
            }
            else if (strcmp(token, "-l") == 0) {
                ll = 1;
            }
            else if (strcmp(token, "-a") == 0) {
                hidden = 1;
            }
            else if((strcmp(token, "-la") == 0) || strcmp(token, "-al") == 0) {
                ll = 1; hidden =1;
            }
            else {
                dir2 = 2;
                n_dir[i++] = token;
                // strcpy(n_dir, token);
                // printf("%s :\n", n_dir);
                // if (ll == 1) {
                //     long_ls(n_dir, hidden);
                // }
                // else {
                //     norm_ls(n_dir, hidden);
                // }
            }
            token = strtok(NULL, " \"\n\t\r");
        }

    }
    if(i==0){
        printf("%s :\n", n_dir[i]);
        if (ll == 1) {
            long_ls(n_dir[i], hidden);
        }
        else {
            norm_ls(n_dir[i], hidden);
        }
        printf("\n");
    }
    else {
        while(j<i) {
            printf("%s :\n", n_dir[j]);
            if (ll == 1) {
                long_ls(n_dir[j], hidden);
            }
            else {
                norm_ls(n_dir[j], hidden);
            }
            printf("\n");
            j++;
        }
    }
}