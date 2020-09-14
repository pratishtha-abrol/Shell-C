# Linux Shell in C

## Overview

This is an attempt to immitate the Linux terminal. It supports most semicolon separated commands, including builtin commands like cd, ls, echo, pwd.
Background and Foreground processes are also handled.

* pwd : prints present working directory.

* cd : changes directory as per the flags given.
    * ``` bash cd
   ``` cd .
       cd ..
       cd ~
       cd <directory>
    ```

* ls : lists contents of a particular directory based on the flags given. All flags are supported, ordering doesn't matter.
    * ``` bash
  ```  ls
       ls -a
       ls -l
       ls -la
       ls -al
       ls <directory>
    ```

* echo : prints a message on the terminal.
    * ``` bash
      ``` echo <"Hello World">
    ```

* pinfo : lists details of a given process id, of the shell in case process id is not specified.
    * ```bash
   ``` pinfo <pid>
       pinfo
    ```

## Foreground and Background processes

* Foreground processes require the shell to halt for the child process to complete before the shell resumes control.
    * ``` bash
   ``` vim
       gedit
       emacs
    ```

* Background processes are specifies with a '&' at the end as a flag. These processes run in the background allowing the shell to execute processes simultaneously.
    * ``` bash
   ``` emacs &
       evince &
       gedit &
    ```

## Running the shell

In order to run the shell on your local device use the following command :
``` bash
make
./a.out
```

## Pseudo Home

The shell considers the home directory to be the directory in which the executable ./a.out resides.

## Exiting the shell

To exit the shell, use the following command :
``` bash
quit
```

## Code Files

* main.c
Contains the main driver code for the shell.

* execute.c
Contains the code to execute each command.

* pwd.c
Contains the function to execute builtin pwd command.

* ls.c
Contains the function to execute builtin ls command, and support all flags.

* cd.c
Contains the function to execute builtin cd command.

* echo.c
Contains the function to execute builtin echo command.

* pinfo.c
Contains the function to execute builtin pinfo command.
