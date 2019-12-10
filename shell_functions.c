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

char ** parseInfo(char * s) {
        fixString(s);
        int index = 0;
        char *found;
        //Create string array. (Will separate each command.)
        char **str = malloc(sizeof(char) * 10);
        for (int i =0 ; i < 10; ++i) {
                str[i] = malloc(20 * sizeof(char));
        }

        while( (found = strsep(&s, ";")) != NULL) {
                printf("%s\n", found);
                strcpy(str[index], found);
                printf("String index: %s\n", str[index]);
                index++;
        }
        return str;
}

void executeInfo(char *s) {
        fixString(s); 
        if(strcmp(s, "cd\n") == 0) {

        }
}
