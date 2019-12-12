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
char ** parseInfo(char * s, char * delimeter) {
        fixString(s);
        int index = 0;
        char *found;
        char **str = calloc(1024, sizeof(char));
        while( (found = strsep(&s, delimeter)) != NULL) {
                str[index] = fixString(found);
                if(!strcmp(delimeter, ";")) {
                        printf("Command %d: %s\n", index, str[index]);
                }
                index++;
        }
        return str;
}

int executeInfo(char **s) {
        int child_status;
        pid_t child_pid;
        printf("First arg: %s  Second arg: %s\n", s[0], s[1]);
        if(strcmp(s[0], "exit") == 0) {
                exit(0);
        }
        if(strcmp(s[0], "cd") == 0) {
                printf("Ran cd!\n");
                if(s[1] == NULL) {
                        chdir(getenv("HOME"));
                }
                else {
                        chdir(fixString(s[1]));
                }
        }
        //Every other command
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
