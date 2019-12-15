#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shell_head.h"

char * fixString(char *s) {
        int index = 0;
        while(s[index] != 0) {
                if(s[index] == '\n') {
                        s[index] = '\0';
                }
                index++;
        }
        return s;
}

//If the delimeter is ;
//This method is specfically used for converting the ; delimiter string into an array of commands. Example: ls -a;cd;cat bruh.txt --> ["ls -a", "cd", "cat bruh.txt"]
//If the mode value is " " 
//This method is specifically used for each index of the ; delimeter string array.
//Essentially used for each command. Example: Gets the string "ls -a" and separates it into
//an array [ls, -a]
//Additionally: This helps with parsing the args for redirection.
char ** parseInfo(char * s, char * delimeter) {
        fixString(s);
        int index = 0;
        char *found;
        char **str = calloc(1024, sizeof(char));
        while( (found = strsep(&s, delimeter)) != NULL) {
                str[index] = fixString(found);
                /*
                if(!strcmp(delimeter, ";")) {
                        printf("Command %d: %s\n", index, str[index]);
                }
                */
                index++;
        }
        return str;
}

//Returns 1 if > is present and 2 if < is present.
int is_redirect(char **s) {
        int index = 0;
        while(s[index] != NULL) {
                //If the argument array has a > in it, return 1.
                if(!strcmp(s[index], ">")) {
                        return 1;
                }
                //If the argument array has a < in it, return 2.
                if(!strcmp(s[index], "<")) {
                        return 2;
                }
                index++;
        }
        return 0;
}

//Returns 1 if a | is in the command line.
int is_pipe(char **s) {
        int index = 0;
        while(s[index] != NULL) {
                //If the argument array has a > in it, return 1.
                if(!strcmp(s[index], "|")) {
                        return 1;
                }
                index++;
        }
        return 0;
}

int executeInfo(char **s) {
        int child_status;
        pid_t child_pid;
        //printf("First arg: %s  Second arg: %s\n", s[0], s[1]);
        if(strcmp(s[0], "exit") == 0) {
                printf("Goodbye World! \n");
                exit(0);
        }
        if(strcmp(s[0], "cd") == 0) {
        //printf("Ran cd!\n");
                if(s[1] == NULL) {
                        chdir(getenv("HOME"));
                }
                else {
                        chdir(fixString(s[1]));
                }
        }
        //Every other command
        else {
                //If there is a redirection:
                if(is_redirect(s) != 0) {
                        //Create file descriptor:
                        int *fd;
                        //The args before and after the > or <.
                        char **redir_args;
                        //Beginning args of redirect separated by a space.
                        char **begin_args;
                        if(is_redirect(s) == 1){
                                redir_args = parseInfo(s[0], ">");
                                begin_args = parseInfo(redir_args[0], " ");
                                printf("Redirecting Args: %s\n", redir_args[1]);
                                printf("Begin arguments: %s\n", begin_args[0]);
                                printf("Well at least out redirecting is detected...\n");
                        }
                        else if(is_redirect(s) == 2) {
                                redir_args = parseInfo(s[0], "<");
                                begin_args = parseInfo(redir_args[0], " ");
                                printf("Well at least in redirecting is detected...\n");
                        }
                }
                else if(is_pipe(s) != 0) {
                                printf("Well at least piping is detected...\n");
                }
                else {
                        child_pid = fork();
                        if(!child_pid) {
                                //Child Process forks previously and executes.
                                execvp(s[0], s);
                                printf("Unrecognized command entered!\n");
                                exit(0);
                        }
                        else {
                                //This ensures that the parent process runs after the child process.
                                wait(&child_status);
                        }
                }
        }
}
