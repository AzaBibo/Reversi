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



# all: reversi
all: client server

client: $(CLIENT_OBJ) $(FUNCTIONS_OBJ)
	mkdir -p bin
	mkdir -p obj
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_OBJ) $(FUNCTIONS_OBJ) $(LIBS)

server: $(SERVER_OBJ) $(FUNCTIONS_OBJ)
	mkdir -p bin
	mkdir -p obj
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_OBJ) $(FUNCTIONS_OBJ) $(LIBS)

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ) $(LIBS)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ) $(LIBS)

$(FUNCTIONS_OBJ): $(FUNCTIONS_SRC) $(FUNCTIONS_H)
	$(CC) $(CFLAGS) -c $(FUNCTIONS_SRC) -o $(FUNCTIONS_OBJ) $(LIBS)
	


# server: server.o functions.o
# 	$(CC) $(CFLAGS) -o server server.o functions.o $(LIBS)

# client: client.o functions.o
# 	$(CC) $(CFLAGS) -o client client.o functions.o $(LIBS)

# server.o: server.c
# 	$(CC) $(CFLAGS) -c server.c -o server.o 	

# client.o: client.c
# 	$(CC) $(CFLAGS) -c client.c -o client.o

# functions.o: functions.c
# 	$(CC) $(CFLAGS) -c functions.c

# functions.o: functions.c functions.h
# 	$(CC) $(CFLAGS) -c functions.c -o functions.o $(LIBS)

# reversi: functions.o reversi.c
# 	gcc reversi.c functions.o -g -o reversi -lncurses

clean:
	rm *.o
	clear
