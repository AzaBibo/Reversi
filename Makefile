.PHONY : all clean

CC = gcc
CFLAGS = -Wall -Werror
LIBS = -lncurses


# all: reversi
all: server client

server: server.o functions.o
	$(CC) $(CFLAGS) -o server server.o functions.o $(LIBS)

client: client.o functions.o
	$(CC) $(CFLAGS) -o client client.o functions.o $(LIBS)

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o 	

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

# functions.o: functions.c
# 	$(CC) $(CFLAGS) -c functions.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c -o functions.o $(LIBS)

# reversi: functions.o reversi.c
# 	gcc reversi.c functions.o -g -o reversi -lncurses

clean:
	rm *.o
	clear
