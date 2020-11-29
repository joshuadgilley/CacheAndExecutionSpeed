CC=gcc
CFLAGS=-Wall

makeit: project.c
	$(CC) project.c -o project $(CFLAGS)
