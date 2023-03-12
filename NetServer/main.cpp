#include<WinSock2.h>
#include<WS2tcpip.h>

#include<iostream>
#include"message.hpp"
#include"netserver.h"
#pragma comment(lib,"ws2_32.lib")

#define port 8888
#define MaxLink 128

int main() {
	Server server;
	if (!server.init("127.0.0.1", 8888)) {
		std::cout << "err:" << std::endl;
		return -1;
	}
	server.start();
	//server.close();
	system("pause");
	return 0;
}
