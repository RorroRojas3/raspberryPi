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

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int clientSocket; // Used to store the socket()
	//int numberOfBytes;	
	char buffer[MAXBYTES];	// Buffer
	char serverIP_address[IPADDRESS];	// Will contain the Server's IP address
	struct addrinfo clientInfo; // Will store the Host information
	struct addrinfo *pClientInfo;	// Will point to Host information
	int error = -1;	// Used as a error checking variable
	//int successSocket = -1;
	//int successConnection = -1;
	char sentMessage[MAXBYTES];	// Used to send messages to Server
	int sentBytes;
	
	char s[256];
	
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
	//clientInfo.ai_flags = AI_PASSIVE; // Assigns Host IP address to socket structures

	error = getaddrinfo(serverIP_address, PORTNUMBER, &clientInfo, &pClientInfo); // pClientInfo points to clientInfo
	if (error != 0)
	{
		printf("Error from function getaddrinfo() %s\n", gai_strerror(error));
		exit(1);
	}
	
	while (pClientInfo != NULL)
	{
		clientSocket = socket(pClientInfo->ai_family, pClientInfo->ai_socktype, pClientInfo->ai_protocol);
		
		// connect(socket of the client, destination port and Host IP address, length in bytes of Server Address structure)
		error = connect(clientSocket, pClientInfo->ai_addr, pClientInfo->ai_addrlen); // Connects to Server
		
		if (clientSocket != -1 && error != -1)
		{
			break;
		}
		else
		{
			pClientInfo = pClientInfo->ai_next;
		}
	}

	if (pClientInfo == NULL)
	{
		printf("Failed to connect to Server\n");
		close(clientSocket);
		exit(1);
	}

	inet_ntop(pClientInfo->ai_family, get_in_addr((struct sockaddr *)pClientInfo->ai_addr), s, sizeof(s));
	printf("client: connecting to %s\n", s);
	
	freeaddrinfo(pClientInfo);

	// recv(socket of client, message storage, maximum size of storage, flag);
	
	while(1)
	{
		error = recv(clientSocket, buffer, MAXBYTES - 1, 0); // Receives message from Server 
		if (error == -1)
		{
			printf("Error on recv() function\n");
			close(clientSocket);
			exit(1);
		}
		else if (error == 0)
		{
			printf("Error, Server has closed connection\n");
			close(clientSocket);
			exit(1);
		}
		else
		{
			buffer[error] = '\0';
			printf("Server sent: '%s'\n", buffer);
			printf("Enter your message: ");
			fgets(buffer, MAXBYTES, stdin);
			sscanf(buffer, "%s", sentMessage);
			sentBytes = send(clientSocket, sentMessage, strlen(sentMessage), 0);		
			if (sentBytes < 0)
			{
				printf("Error on the send() function");
				close(clientSocket);
				exit(1);
			}
		}
	}

		
	close(clientSocket);
	return 0;
}

