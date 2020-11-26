#include <stdio.h>
#include <winsock.h>
#include <string.h>

#define BUFFERSIZE 64

void main(int argc, char* argv[])
{
	char buffer[BUFFERSIZE];

	/*if ( argc < 2 )
	{
		fprintf(stderr, "Invalid Arguments.\n");
		fprintf(stdout, "Format: gcc server.c 8000\n");
		exit(1);
	}*/

	//For Windows Programmers
	WSADATA wsadata;
	if ( WSAStartup(MAKEWORD(2,2), &wsadata) )
	{
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}

	//Socket Creation
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //socket file descripter 
	if ( serverSocket == SOCKET_ERROR )
	{
		fprintf(stderr, "Socket Creation Failed.\n");
		exit(1);
	}

	SOCKADDR_IN serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);	//or 127.0.0.1 localaddr
	serverAdress.sin_port = htons(8000);

	if( bind(serverSocket, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) == SOCKET_ERROR )
	{
		fprintf(stderr, "Bind Failed.\n");
		exit(1);
	}

	const int queueLen = 5;
	if ( listen(serverSocket, queueLen) == SOCKET_ERROR )
	{
		fprintf(stderr, "Listen Failed.\n");
		exit(1);
	}

	SOCKADDR_IN clientAddress;
	int clientAddressSize = sizeof(clientAddress);
	SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
	if ( clientSocket == SOCKET_ERROR )
	{
		fprintf(stderr, "Accept Failed.\n");
		exit(1);
	}

	int numberOfByte = recv(clientSocket, buffer, BUFFERSIZE, 0);
	if (numberOfByte == SOCKET_ERROR)
	{
		fprintf(stderr, "Receive Failed.\n");
		exit(1);
	}
	fprintf(stdout, "%s", buffer);
	/*numberOfByte = send(clientSocket, buffer, BUFFERSIZE, 0);
	if (numberOfByte == SOCKET_ERROR)
	{
		fprintf(stderr, "Send Failed.\n");
		exit(1);
	}*/

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
}
