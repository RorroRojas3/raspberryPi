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
#include <sys/wait.h>

#define PORTNUMBER "50505"
#define MAXBYTES 256
#define IPADDRESS 130
#define MAXCLIENTS 5

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

char *stringAlloc(char *string, int lengthOfString)
{
    int c1;
    char *result;
    result = (char *)calloc(lengthOfString, sizeof(char));
    for (c1 = 0; (string[c1] != '\0') && (string[c1] != '\n') && (c1 < lengthOfString); c1++)
    {
        result[c1] = string[c1];
    }
    result[c1] = '\0';
    return result;
}

void stringFree(char *string)
{
    free(string);
}

int main(int argc, char *argv[])
{
    int serverSocket; // Used to store the socket()
    int clientSocket;
    int sentBytes = -2; // Used to keep track of bytes sent to Client
    char buffer[MAXBYTES];  // Buffer
    struct addrinfo serverInfo; // Will store the Server's information
    struct addrinfo *pServerInfo;   // Will point to Server Information
    int error = -2; // Used as a error checking variable
    char *sentMessage; // Used to send messages to Server
    struct sockaddr_storage clientIP_address; // Used to store Client(s) addresses
    socklen_t sin_size; // ?????
    int child = -1;
    int status = -1;

    memset(&serverInfo, 0, sizeof(serverInfo)); // Emtpies garbage from structure

    serverInfo.ai_family = AF_UNSPEC; // IP can be either IPv4 or IPv6
    serverInfo.ai_socktype =  SOCK_STREAM; // TCP Connection
    serverInfo.ai_flags = AI_PASSIVE; // Assigns Server's IP address to socket structures

    error = getaddrinfo(NULL, PORTNUMBER, &serverInfo, &pServerInfo); // pServerInfo points to serverInfo
    if (error != 0)
    {
        printf("Error from function getaddrinfo() '%s'\n", gai_strerror(error));
        exit(1);
    }

    serverSocket = socket(pServerInfo->ai_family, pServerInfo->ai_socktype, pServerInfo->ai_protocol);
    if (serverSocket == -1)
    {
        printf("Error, socket() failed\n");
        free(pServerInfo);
        exit(1);
    }

    error = bind(serverSocket, pServerInfo->ai_addr, pServerInfo->ai_addrlen);
    if (error == -1)
    {
        close(serverSocket);
        printf("Error on bind() function\n");
        exit(1);
    }

    freeaddrinfo(pServerInfo);

    error = listen(serverSocket, MAXCLIENTS);
    if (error == -1)
    {
        printf("Error on listen() function\n");
        close (serverSocket);
        exit(1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    }

    printf("Server waiting for clients\n");
    while(1)
    {
        sin_size = sizeof(clientIP_address);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientIP_address, &sin_size);
        if (clientSocket == -1)
        {
            printf("Error on accept() function\n");
            close(serverSocket);
            exit(1);
        }
        else
        {
            break;
        }
    }

    inet_ntop(clientIP_address.ss_family,get_in_addr((struct sockaddr *)&clientIP_address), buffer, sizeof(buffer));
	printf("Server: got connection from %s\n", buffer);

    // Creates a child process
    child = fork();
    if (child == 0) // Child process
    {
        while(1)
        {
            memset(buffer, '\0', sizeof(buffer));
            printf("Enter your message: ");
            fgets(buffer, MAXBYTES, stdin);
            sentMessage = stringAlloc(buffer, strlen(buffer));
            // send(socket of Server, message to send, maximum size of storage, flag)
            sentBytes = send(clientSocket, sentMessage, strlen(sentMessage), 0); // Send message to Client
            if (sentBytes < 0)
            {
                printf("Error on the send() function\n");
                close(serverSocket);
                stringFree(sentMessage);
                exit(1);
            }
            error = recv(clientSocket, buffer, MAXBYTES - 1, 0);
            if (error == -1)
            {
                printf("Error on recv() function\n");
                close(serverSocket);
                close(clientSocket);
                stringFree(sentMessage);
                exit(1);
            }
            else if (error == 0)
            {
                printf("Error, Client has closed connection\n");
                close(serverSocket);
                close(clientSocket);
                stringFree(sentMessage);
                exit(1);
            }
            else
            {
                buffer[error] = '\0';
                printf("Client sent: %s\n", buffer);
                stringFree(sentMessage);
            }
        }
        close(serverSocket);
    }
    else if (child > 0) // Parent process
    {
        wait(&status);
        close(clientSocket);
    }
    else // Child could not be created due to memory
    {
        printf("Child process could not be created\n");
    }
    
    close(serverSocket);
    
}
