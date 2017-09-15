#include <iostream>
#include "Utils.h"

void main( ) {
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
		pnautils::throwWSAError(std::string("Startup"));
	}
	SOCKADDR_IN addr;
	int addrLength = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(4814);
	addr.sin_family = AF_INET;
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
#ifdef _DEBUG
	std::cout << "Press any key to exit...";
	std::cin.get( );
#endif // _DEBUG
}
