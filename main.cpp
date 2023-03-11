#include"message.hpp"
#include"netclient.h"
#pragma comment(lib,"ws2_32.lib")

#define port 8888

int main() {
	Client client;
	if (!client.init("127.0.0.1", port)) {
		return -1;
	}
	client.start();
	system("pause");
	return 0;
}