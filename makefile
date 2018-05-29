CC=gcc
CFLAGS=-std=c99 -g3 -pedantic -Wall -Wextra

db: main.o interface.o
	$(CC) -o db main.o interface.o

main.o: main.c interface.h
	$(CC) $(CFLAGS) -c main.c

interface.o: interface.c interface.h
	$(CC) $(CFLAGS) -c interface.c

clean:
	rm -f *.o main
