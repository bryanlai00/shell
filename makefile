all: main.o shell_functions.o 
	gcc -o sbash main.o shell_functions.o

main.o: main.c
	gcc -c main.c

shell_functions.o: shell_functions.c shell_head.h
	gcc -c shell_functions.c shell_head.h

run:
	./sbash
