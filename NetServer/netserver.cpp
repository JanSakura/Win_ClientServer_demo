#include "netserver.h"
#include<WS2tcpip.h>
#include<assert.h>
#define MaxLink 128

Server::Server():servSock(INVALID_SOCKET){}

Server::~Server(){
	close();
}

void Server::close(){
	if (servSock != INVALID_SOCKET) {
		closesocket(servSock);
		for (auto client : clientList) {
			closesocket(client);
		}
		WSACleanup();
	}
}

bool Server::init(const char* ip, unsigned short port) {
	WSADATA data{};
	if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR) {
		perror("WSAStartup func err:");
		return false;
	}
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET) {
		perror("server socket func err:");
		WSACleanup();
		return false;
	}
	sockaddr_in servAddr{};
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr.S_un.S_addr);
	if (bind(servSock, (sockaddr*)&servAddr, sizeof(sockaddr)) == SOCKET_ERROR) {
		perror("bind func err:");
		closesocket(servSock);
		servSock = INVALID_SOCKET;
		WSACleanup();
		return false;
	}
	if (listen(servSock, MaxLink) == SOCKET_ERROR) {
		perror("listen func err:");
		closesocket(servSock);
		WSACleanup();
		return false;
	}
	return true;
}

bool Server::start(){
	if (!coreFunc()) {
		return false;
	}
}

bool Server::coreFunc(){
	assert(servSock != INVALID_SOCKET);
	bool flag = true;
	while (flag) {
		fd_set fdRead;
		FD_ZERO(&fdRead);
		FD_SET(servSock, &fdRead);
		for (auto client : clientList) {
			FD_SET(client, &fdRead);
		}
		//超时等待时间，设置为1s,第一个参数是秒，第二个是微秒10^-6s
		timeval tval{ 1,0 };
		int selectRes = select(0, &fdRead, nullptr, nullptr, &tval);
		if (selectRes > 0) {
			for (unsigned i = 0; i < fdRead.fd_count; ++i) {
				if (fdRead.fd_array[i] == servSock) {
					SOCKET clientSock = accept(servSock, nullptr, nullptr);
					if (clientSock == INVALID_SOCKET) {
						perror("accept func err:");
						break;
					}
					clientList.push_back(clientSock);
				}
				else {
					recvMsg(fdRead,fdRead.fd_array[i]);
				}
			}
		}
		else if (selectRes == 0) {
			std::cout << "select func something else" << std::endl;
			continue;
		}
		else {
			perror("select func err:");
			return false;
		}
	}
	return true;
}

bool Server::recvMsg(fd_set& fdRead,SOCKET clntSock){
	Header header;
	int recvRes = recv(clntSock, (char*)&header, sizeof(Header), 0);
	if (recvRes <= 0) {
		std::cout << "recv func err:" << WSAGetLastError << std::endl;
		return false;
	}
	switch (header.cmd)
	{
	case CMD::LOGIN: {
		Login login;
		int recvRet = recv(clntSock, (char*)&login + sizeof(Header), sizeof(Login) - sizeof(Header), 0);
		if (recvRet <= 0) {
			std::cout << "recv func err:" << WSAGetLastError << std::endl;
			return false;
		}
		LoginResult loginResult(10);
		if (send(clntSock, (char*)&loginResult, sizeof(LoginResult), 0) < 0) {
			std::cout << "send func err:" << WSAGetLastError << std::endl;
			return false;
		}
		break;
	}
	case CMD::LOGOUT: {
		Logout logout;
		int recvRet = recv(clntSock, (char*)&logout + sizeof(Header), sizeof(Logout) - sizeof(Header), 0);
		if (recvRet <= 0) {
			std::cout << "recv func err:" << WSAGetLastError << std::endl;
			return false;
		}
		LogoutResult logoutResult(10);
		if (send(clntSock, (char*)&logoutResult, sizeof(LogoutResult), 0) < 0) {
			std::cout << "send func err:" << WSAGetLastError << std::endl;
			return false;
		}
		break;
	}
	default:
		break;
	}
}

bool Server::conductMsg()
{
	return false;
}

