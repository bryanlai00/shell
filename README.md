# A Shell Written in C
As the title suggests, this is an interactive bash shell written in C. 

**You might be thinking:**

*What's the point of creating a bash shell in C? I mean in Python you can simply get a bash shell by typing os.system()...*

**My Answer:**

Hey let's look at the features of this C Shell!

## Implementations of the C Shell ##
- Can parse and execute any command installed on your computer, along with specific command line arguments.
- Can run multiple commands if separated by a semi-colon (;).
- Can redirect inputs using < and >. However, it is currently unable to redirect twice. (Cannot double redirect).
- Can use unnamed pipes.

## Bugs ##
- Double (+ more) redirection currently does not work. Throughout the methods used to implement direction, it only detects either > or <, not a combination of both.
- Double (+ more) pipes currently do not work. Additionally, when you use pipes outside of the directory of the file, it responds with a not found error. Here is a specififc example when testing the TEST_COMMANDS.txt file.
<code>
sh: 1: 64-bit.deb: not found                                                                                                                                                                               
sh: 2: Library: not found                                                                                                                                                                                   
sh: 3: linkedListC: not found                                                                                                                                                                               
sh: 4: Make.class: not found                                                                                                                                                                                
sh: 5: makefile: not found                                                                                                                                                                                  
sh: 6: Make.java: not found                                                                                                                                                                                 
sh: 7: mcstatus: not found                                                                                                                                                                                  
sh: 8: Merge.class: not found                                                                                                                                                                               
sh: 9: Merge.java: not found                                                                                                                                                                                
sh: 10: mjpfp: not found                   
</code>

## So how was this made? 

Well, obviously in C. Here are the specific methods though:
### shell.c
This is the main file. Inside it imports a numerous amount of libraries including:
-stdio.h
-stdlib.h
-unistd.h
-string.h
-sys/wait.h
-etc.
It takes in an input from the user, parses it, and executes it. These specific methods and implementations are found in...
### shell_functions.c
This is specifically the functions file. Inside are the following functions:
#### char * fixString(char * s)
This method removes the newline character at the end of a user's input. Afterwards, it returns this new string. (This prevents confusion, and allows the commands to be parsed correctly.) 
#### char ** parseInfo(char * s, char * delimiter) 
This method deals with **most** of the parsing of a user's input. It iterates through the string, separating s into two strings based on a certain delimiter. For example if the delimiter is ";"
<code> "ps ; ls -a" --> "ps", "ls -a" </code> 

The other delimeter used with this function is an empty space, which separates the beginning input into the command and its specifc arguments. For example: 
<code> "ls -a" --> "ls" "-a" </code>
#### int is_redirect(char ** s) 
This method takes in a string array and returns one of three values. 
- If there is a > in the string array, the method returns 1.
- If there is a < in the string array, the method returns 2.
- If > or < is not present, the method returns 0. 
#### int is_pipe(char ** s)
Similar to is_redirect, this method takes in a string array and returns one of two values.
- If there is a | in the string array, the method returns 1.
- If a | is not present, the method returns 0.
#### void run_redirect(char ** s) 
This method takes care of redirection. There are comments that detail each process inside of the file.
#### void run_pipe(char ** s)
This method takes care of pipes. Likewise to run_redirect, there are comments that show testing and information about each part.
#### void executeInfo(char ** s)
This method takes care of all execution. It runs every single command line input (separated by the delimeter ;) as it is in a for loop back in **shell.c**. In addition, it creates a child process by forking in order to not interfere with the parent process. Additionally, it deals with cd and exit.
