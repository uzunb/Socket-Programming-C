#include <stdio.h>
#include <winsock.h>
#include <string.h>

#define BUFFERSIZE 64

void main(int argc, char* argv[])
{
	char buffer[BUFFERSIZE];

	/*if (argc < 2)
	{
		fprintf(stderr, "Invalid Arguments.\n");
		fprintf(stdout, "Format: gcc server.c 8000\n");
		exit(1);
	}*/

	//For Windows Programmers
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}

	//Socket Creation
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //socket file descripter 
	if (serverSocket == SOCKET_ERROR)
	{
		fprintf(stderr, "Socket Creation Failed.\n");
		exit(1);
	}

	SOCKADDR_IN serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1");	//or 127.0.0.1 localaddr
	serverAdress.sin_port = htons(8000);

	if(connect(serverSocket, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) < 0)
	{
		fprintf(stderr, "Connect Failed.\n");
		exit(1);
	}

	char message[] = "Bismillah!";	
	if (send(serverSocket, message, strlen(message), 0) == SOCKET_ERROR)
	{
		fprintf(stderr, "Connect Failed.\n");
		exit(1);
	}

	closesocket(serverSocket);
	WSACleanup();

	system("pause");
}
