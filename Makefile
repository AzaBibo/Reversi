.PHONY : all clean

CC = gcc
CFLAGS = -Wall -Werror
LIBS = -lncurses
CLIENT_SRC = ./src/client.c
SERVER_SRC = ./src/server.c
FUNCTIONS_SRC = ./src/functions.c
FUNCTIONS_H = ./src/functions.h
CLIENT_OBJ = ./obj/client.o
SERVER_OBJ = ./obj/server.o
FUNCTIONS_OBJ = ./obj/functions.o
CLIENT_BIN = ./bin/client
SERVER_BIN = ./bin/server


all: client server

client: $(CLIENT_OBJ) $(FUNCTIONS_OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_OBJ) $(FUNCTIONS_OBJ) $(LIBS)

server: $(SERVER_OBJ) $(FUNCTIONS_OBJ)
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_OBJ) $(FUNCTIONS_OBJ) $(LIBS)

$(CLIENT_OBJ): $(CLIENT_SRC)
	mkdir -p obj
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ) $(LIBS)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ) $(LIBS)

$(FUNCTIONS_OBJ): $(FUNCTIONS_SRC) $(FUNCTIONS_H)
	$(CC) $(CFLAGS) -c $(FUNCTIONS_SRC) -o $(FUNCTIONS_OBJ) $(LIBS)
	

# reversi: functions.o reversi.c
# 	gcc reversi.c functions.o -g -o reversi -lncurses

clean:
	rm -rf ./obj ./bin
	clear
