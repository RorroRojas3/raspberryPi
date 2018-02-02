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
	int clientSocket; // Used to store the socket()
	//int numberOfBytes;	
	char buffer[MAXBYTES];	// Buffer
	char serverIP_address[IPADDRESS];	// Will contain the Server's IP address
	struct addrinfo clientInfo; // Will store the Host information
	struct addrinfo *pClientInfo;	// Will point to Host information
	int error = -1;	// Used as a error checking variable
	//char sentMessage[INET6_ADDRSTRLEN];	// Used to send messages to Server
	
	if (argc != 2)
	{
		printf("Please enter IP address of Server\n");
		printf("Usage -> '/./execute IP_Address'\n");
		exit(1);
	}	
	else
	{
		strcpy(serverIP_address, argv[1]);
	}

	memset(&clientInfo, 0, sizeof(clientInfo)); // Empties garbage from structure

	clientInfo.ai_family = AF_UNSPEC; // IP can be either IPv4 or IPv6
	clientInfo.ai_socktype = SOCK_STREAM; // TCP connection
	clientInfo.ai_flags = AI_PASSIVE; // Assigns Host IP address to socket structures

	error = getaddrinfo(NULL, PORTNUMBER, &clientInfo, &pClientInfo); // pClientInfo points to clientInfo
	if (error != 0)
	{
		printf("Error from function getaddrinfo() %s\n", gai_strerror(error));
		exit(1);
	}
	
	clientSocket = socket(pClientInfo->ai_family, pClientInfo->ai_socktype, pClientInfo->ai_protocol);
	if (clientSocket == -1)
	{
		printf("Error, socket failed\n");
		free(pClientInfo);
		exit(1);
	}
	
	// connect(socket of the client, destination port and Host IP address, length in bytes of Server Address structure)
	error = connect(clientSocket, pClientInfo->ai_addr, pClientInfo->ai_addrlen); // Connects to Server
	if (error == -1)
	{
		printf("Error, connection between Client and Server failed\n");
		free(pClientInfo);
		close(clientSocket);
		exit(1);
	}

	// recv(socket of client, message storage, maximum size of storage, flat);
	error = recv(clientSocket, buffer, MAXBYTES, 0); // Receives message from Server 
	if (error == -1)
	{
		printf("Error on recv() function\n");
		free(pClientInfo);
		close(clientSocket);
		exit(1);
	}
	else if (error == 0)
	{
		printf("Error, Server has closed connection\n");
		free(pClientInfo);
		close(clientSocket);
		exit(1);
	}
	else
	{
		buffer[MAXBYTES] = '\0';
		printf("Server sent: '%s'\n", buffer);
	}


	free(pClientInfo); // Frees the Linked List
	close(clientSocket);
	return 0;
}

