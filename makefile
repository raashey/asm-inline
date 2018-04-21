all: lab4

lab4 : lab4.o
	gcc -o lab4 lab4.o
lab4.o : lab4.c
	gcc -c lab4.c

clean :
	rm lab4 *.o
