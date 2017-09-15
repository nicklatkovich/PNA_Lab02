#include <iostream>
#include "Utils.h"

void main( ) {
	SOCKADDR_IN addr = pnautils::startSession( );
	int addrLength = sizeof(addr);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	std::cout << "Server created" << std::endl;
	std::cout << "W8ing 4 connection..." << std::endl;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrLength);
	if (newConnection == 0) {
		pnautils::throwWSAError(std::string("Create new connection"));
	}
	std::cout << "Client connected" << std::endl;
	while (true) {
		char recvMessage[256];
		recv(newConnection, recvMessage, sizeof(recvMessage), NULL);
		if (strlen(recvMessage) == 0) {
			break;
		}
		send(newConnection, recvMessage, sizeof(recvMessage), NULL);
		std::cout << recvMessage << std::endl;
	}
#ifdef _DEBUG
	std::cout << "Press any key to exit...";
	std::cin.get( );
#endif // _DEBUG
}
