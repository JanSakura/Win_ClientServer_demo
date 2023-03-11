#ifndef _NET_SERVER_
#define _NET_SERVER_
#include"message.hpp"
#include<WinSock2.h>
#include<iostream>
#include<list>

class Server {
public:
	Server();
	virtual~Server();
	void close();
	bool init(const char* ip, unsigned short port);
	bool start();
	bool recvMsg(fd_set& fdRead,SOCKET clntSock);
	bool conductMsg();

private:
	SOCKET servSock;
	std::list<SOCKET> clientList;
	bool coreFunc();
};


#endif // !_NET_SERVER_
