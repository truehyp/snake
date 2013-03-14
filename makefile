CC = gcc
#PATH += /usr/include/gtk2.0
LDLIBS = `pkg-config --libs gtk+-2.0`
CFLAGS = -Wall -g `pkg-config --cflags --libs gtk+-2.0`

main:main.o snake.o
	$(CC) $(LDLIBS) main.o snake.o -o main

main.o:main.c
	$(CC) -c main.c $(CFLAGS) 
snake.o:snake.c snake.h
	$(CC) -c snake.c $(CFLAGS) 

clean :
	-rm -f *.o
	-rm -f main
