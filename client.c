// Library Declaration Section

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORTNUMBER "50505"
#define MAXBYTES 256
#define IPADDRESS 130

int main(int argc, char *argv[])
{
	int socket, numberOfBytes;
	char buffer[MAXBYTES];
	char ip_address[IPADDRESS];
	struct addrinfo hints, *servinfo, *p;
	int error = -1;
	char sentMessage[INET6_ADDRSTRLEN];
	
	if (argc != 2)
	{
		printf("Please enter IP address of Server\n");
		printf("Usage -> '/./execute IP_Address'\n");
		exit(1);
	}	
	else
	{
		strcpy(ip_address, argv[1]);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // Type of IP can be either IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // Type of socket is TCP

	error = getaddrinfo(ip_address, PORTNUMBER, &hints, &servinfo);

	if (error != 0)
	{
		printf("Error on function getaddrinfo(): %s\n", gai_strerror(error));
		exit(1);
	}

	

}

