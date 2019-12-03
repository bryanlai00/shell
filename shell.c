#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell_head.h"

//Part 1: Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command. The parent process should wait until the exec'd program exits and then it should read the next command. Check chdir();





//Part 2: Read and separate multiple commands on one line with ;. That is, the line ls -l ; echo hello should first run the command ls -l and then echo hello.  
//Note: Use sscanf when separating the line: (Part 2)


//Part 3: Implement simple redirection using > (redirecting stdout) and < (redirecting stdin). - This will be explained in class. 


// Part 4:Implement simple pipes, that is: ls | wc would run ls and use the output from ls as the input for wc. - This will be explained in class.
//Check out popen() for this. 

