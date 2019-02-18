bag: main.o bow.o mymalloc.o bow.h mymalloc.h
	gcc -Wall -ansi -pedantic  main.o bow.o mymalloc.o -o bag

main: main.c main.o bow.h
	gcc -Wall -ansi -pedantic -c main.c -o main.o

bow: bow.c bow.o bow.h
	gcc -Wall -ansi -pedantic -c bow.c -o -bow.o

mymalloc: mymalloc.c mymalloc.o mymalloc.h
	gcc -Wall -ansi -pedantic -c mymalloc.c -o -mymalloc.o

clean:
	rm -i bag bow.o main.o
