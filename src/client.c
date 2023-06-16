#include "functions.h"

int main (int argc, char const ** argv)
{
	if (argc != 3)
        error("Usage: ./client [IP addr] [Port num]") ;

	int conn_fd = connect_ipaddr_port(argv[1], atoi(argv[2])) ;
	
	chat_client(conn_fd) ;

	shutdown(conn_fd, SHUT_RDWR) ;

	return EXIT_SUCCESS ;
} 