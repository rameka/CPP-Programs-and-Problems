/*
 * Server.cpp : This program consists of server for the echo server, which sends the message back to  * client
 * Author: Ramakrishna Sayee Meka, Syracuse University
 */


#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib");
using namespace std;

void main() {
	//initialize minsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0) {
		cerr << "Can't Initialize winsock! Quitting" << endl;
		WSACleanup();
		return;
	}
	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket" << endl;
	}
	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //inet_pton ... also work
	bind(listening, (sockaddr *)&hint, sizeof(hint));

	//Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	//wait for a connection
	sockaddr_in client;
	int clientsize = sizeof(client);
	SOCKET clientSocket = accept(listening, (sockaddr *)&client, &clientsize);

	char host[NI_MAXHOST]; //client's remote name
	char service[NI_MAXSERV]; //service (i.e., port) the client is connected on
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);
	if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		cout << host << "connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}
	//close listening socket
	closesocket(listening);
	//while loop; accept and echo message back to client
	char buf[4096];
	while (true) {
		ZeroMemory(buf, 4096);
		//wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR) {
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}
		if (bytesReceived == 0) {
			cout << "client disconnected " << endl;
			break;
		}
		send(clientSocket, buf, bytesReceived + 1, 0);
	}
	//close the socket
	closesocket(clientSocket);
	//cleanup winsock
	WSACleanup();
}