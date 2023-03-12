#include "netclient.h"
#include<WS2tcpip.h>
#include<iostream>
Client::Client():servSock(INVALID_SOCKET){}

Client::~Client(){
    close();
}

void Client::close(){
	if (servSock != INVALID_SOCKET) {
		closesocket(servSock);
		WSACleanup();
	}
}

bool Client::init(const char* ip, unsigned short port){
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR) {
		perror("WSAStartup func err");
		return false;
	}
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET) {
		std::cout << "socket func err:" << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}

	sockaddr_in servAddr{};
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr.S_un.S_addr);
	if (connect(servSock, (sockaddr*)&servAddr, sizeof(sockaddr)) == SOCKET_ERROR) {
		std::cout << "connect func err:" << WSAGetLastError() << std::endl;
		closesocket(servSock);
		servSock = INVALID_SOCKET;
		WSACleanup();
		return false;
	}
	std::cout << "connect success" << std::endl;
}

bool Client::start(){
	bool flag = true;
	while (flag) {
		Login login("aaa", "bbb");
		if (send(servSock, (char*)&login, sizeof(Login), 0) < 0) {
			std::cout << "send func err:" << WSAGetLastError() << std::endl;
			return false;
		}
		LoginResult loginResult;
		if (recv(servSock, (char*)&loginResult, sizeof(LoginResult), 0) <= 0) {
			std::cout << "recv func err:" << WSAGetLastError() << std::endl;
			return false;
		}
		std::cout << loginResult.loginResultNum << loginResult.dataLen << std::endl;
		Sleep(100);
	}
}
