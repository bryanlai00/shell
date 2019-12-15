#include <stdio.h>
#include <stdlib.h>

char * fixString(char * s);
char ** parseInfo(char * s, char * delimeter);
int executeInfo(char ** s);
int is_redirect(char ** s);
int is_pipe(char ** s);
void run_redirect(char ** s);
