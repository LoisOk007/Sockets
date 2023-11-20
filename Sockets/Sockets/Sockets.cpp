#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
//#include "stdafx.h"

using namespace std;
int main()
{
	SOCKET serverSocket, acceptSocket;
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

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Error at socket():" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
		cout << "socket() is OK!" << endl;

	sockaddr_in service;
	service.sin_family = AF_INET;

	InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		cout << "bind() failed:" << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "bind() is OK!" << endl;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
		cout << "listen():Error listening on Socket:" << WSAGetLastError() << endl;
	else
		cout << "Listen() is OK! Waiting somebody..." << endl;

	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET)
	{
		cout << "accept failed:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Accepted connection!" << endl;
	system("pause");
	char receiveBuffer[200] = "";
	int byteCount = recv(acceptSocket, receiveBuffer, 200, 0);
	if (byteCount < 0) {
		printf("error %1d.\n", WSAGetLastError());
		return 0;
	}
	else
	{
		printf("Received: %s \n", receiveBuffer);
	}
	
	WSACleanup();
}
