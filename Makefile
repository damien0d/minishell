all: main
main: main.o exec.o bool.o supp.o
	gcc main.o exec.o bool.o supp.o -o minishell

supp.o: supp.c supp.h
	gcc -c supp.c

bool.o: bool.c bool.h
	gcc -c bool.c

exec.o: exec.c exec.h supp.h bool.h
	gcc -c exec.c

main.o: main.c exec.h bool.h supp.h
	gcc -c main.c

clean: 
	rm *.o
