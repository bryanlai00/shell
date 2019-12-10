all: shell.o shell_functions.o
	gcc -o sbash shell.o shell_functions.o

shell.c: shell.c
	gcc -c shell.c

shell_functions.o: shell_functions.c shell_head.h
	gcc -c shell_functions.c shell_head.h

run:
	./sbash
