#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell_head.h"

char * fixString(char *s) {
        int index = 0;
        while(s[index] != 0) {
                if(s[index] == '\n') {
                        s[index] = 0;
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
        char **str = malloc(sizeof(char) * 10);
        for (int i =0 ; i < 10; ++i) {
                str[i] = malloc(20 * sizeof(char));
        }
        while( (found = strsep(&s, delimeter)) != NULL) {
                strcpy(str[index], found);
                if(!strcmp(delimeter, ";")) {
                        printf("Command %d: %s\n", index, str[index]);
                }
                index++;
        }
        return str;
}

void executeInfo(char **s) {
        printf("First arg: %s  Second arg: %s \n", s[0], s[1]);
        //If the command is ls.
        if(strcmp(s[0], "cd") == 0) {
                printf("Ran cd!\n");
                if(s[1] = NULL) {
                        chdir(getenv("HOME"));
                }
                else {
                        chdir(s[1]);
                }
        }
        //Every other command
        else {
                execvp(s[0], s);
        }
}
