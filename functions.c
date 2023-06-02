#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/socket.h>
#include "functions.h"

void help() {
    printf("Description of Reversi Game:\n");
    printf("A host will be color black \"X\"\n");
    printf("A connecting user will be color white \"O\"\n");
}

void error(char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}
