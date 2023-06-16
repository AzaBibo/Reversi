.PHONY : all clean

CC = gcc
CFLAGS = -Wall -Werror

# all: reversi
all: server client

server: server.o functions.o
	$(CC) $(CFLAGS) -o server server.o functions.o

client: client.o functions.o
	$(CC) $(CFLAGS) -o client client.o functions.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

# functions.o: functions.c
# 	$(CC) $(CFLAGS) -c functions.c

functions.o: functions.c functions.h
	gcc -c functions.c -o functions.o -lncurses

# reversi: functions.o reversi.c
# 	gcc reversi.c functions.o -g -o reversi -lncurses

clean:
	rm reversi *.o
	clear
