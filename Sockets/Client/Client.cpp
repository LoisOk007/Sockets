#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
//#include "stdafx.h"

using namespace std;

int main()
{
	SOCKET clientSocket;
	int port = 55555;
	const char* adr = "127.0.0.1";
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "The Winsock dll not found!" << endl;
		return 0;
	}
	else
	{
		cout << "The Winsock dll found!" << endl;
		cout << "Status:" << wsaData.szSystemStatus << endl;
	}

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error at socket():" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
		cout << "socket() is OK!" << endl;

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, L"127.0.0.1", &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "connect() failed:" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "connect() is OK!" << endl;
	}

	char buffer[200];
	while (true)
	{
		printf("Enter your message:");
		cin.getline(buffer, 200);
		int byteCount = send(clientSocket, buffer, 200, 0);
		if (buffer == "Close") {
			closesocket(clientSocket);
			WSACleanup();
			break;
		}
		if (byteCount == SOCKET_ERROR)
		{
			printf("Server send error %1d.\n", WSAGetLastError());
			return -1;
		}
		else
		{
			printf("Server: sent %1d bytes \n", byteCount);
		}
	}
	return 0;
}