#ifndef _NET_CLIENT_
#define _NET_CLIENT_
#include"message.hpp"
#include<WinSock2.h>
class Client {
public:
	Client();
	virtual~Client();
	void close();
	bool init(const char* ip, unsigned short port);
	bool start();

private:
	SOCKET servSock;
};

#endif // !_NET_CLIENT_

