/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parsecmd.h"

// No global variables allowed.

void freeArgs(char** args);
void sigchld_handler(int sig);

int main(int argc, char **argv) {
    char cmdline[MAXLINE];
    char oldpwd[MAXLINE];
    char cwd[MAXLINE]; //the current working directory
    char **args;
    int bg; //checks if background or foreground
    pid_t pid;
    char* ret; //the return value for getcwd
    int vpret; //the return value for execvp
    int argLen = 0; //the length of the args

    signal(SIGCHLD, sigchld_handler);

    // initialize previous directory to be "." (the current directory)
    strcpy(oldpwd, "."); 

    // initialize path to home directory
    ret = getenv("HOME");
    strcpy(cwd, ret);

    while (1) {
        // (1) print the shell prompt
        printf("\ncs31shell> ");
        fflush(stdout);

        // (2) read in the next command entered by the user
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
            perror("fgets error");
        }

        if (feof(stdin)) { /* End of file (ctrl-D) */
            fflush(stdout);
            exit(0);
        }

        args = parse_cmd_dynamic(cmdline, &bg);

        // dtermines number of arguments in command line
        while(args[argLen]!=NULL){ 
            argLen++;
        }

        // checks if we are exiting
        if (strcmp(args[0], "exit") == 0) { 
            freeArgs(args);
            printf("Exiting shell! I'll miss you :D\n");
            exit(0);
        }

        // handles changing directories
        if (strcmp(args[0], "cd") == 0) {
           char* home = getenv("HOME");

            if (args[1] == NULL) { //case where we return to home
                chdir(home);
            } else if (strcmp(args[1], "-") == 0) { //case where we go back
                if (chdir(oldpwd) == 1) {
                    printf("Unable to determine the current directory :(");
                    exit(1);
                }
                chdir(oldpwd);
                strcpy(oldpwd, cwd);
            } 
            
            int i = 1;
            while(args[i] != NULL) { //case where we enter into <path>
                char* cwdret = getcwd(cwd, MAXLINE);
                if (cwdret == NULL) {
                    printf("Unable to determine the current directory :(");
                    exit(1);               
                }
                strcpy(oldpwd, cwd);
                chdir(args[i]);
                i++;
            }
        }   

        //checks if running in foreground
        if (bg == 0) {
            pid = fork();
            if (pid == 0) {
                vpret = execvp(args[0], args);
                fflush(stdout);
                if (vpret < 0) { //if execvp fails
                    printf("%s: command cannot be found :(\n", args[0]);
                    freeArgs(args);
                    exit(vpret);
                }
            } else if (pid != -1) {
                pid = waitpid(pid, NULL, 0); //we wait to reap :)
            }
        }
        // else we are running in the background
        else {
            pid = fork();
            if (pid == 0) {
                vpret = execvp(args[0], args);
                if (vpret < 0) { //if execvp fails
                    printf("%s: command cannot be found :( \n", args[0]);
                    exit(vpret);
                }
            }
        }
        freeArgs(args);
    }
    return 0;
}

//function that handles the signal. checks to see if it is a child, recieves 
//sigchld signal from chld in order to reap.
//@sig : the integer containing the signal
void sigchld_handler(int sig) {
    int status;
    pid_t pid;
    while ( (pid = waitpid(-1, &status, WNOHANG)) > 0) {
    }
}

//function to free up the memory taken by args
//@args the array to be freed
void freeArgs(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        free(args[i]);
        i++;
    }
    free(args);
    args = NULL;
}