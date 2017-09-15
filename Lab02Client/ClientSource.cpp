#include <iostream>
#include "Utils.h"

void main( ) {
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
		pnautils::throwWSAError("Startup");
	}
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(4814);
	addr.sin_family = AF_INET;
	SOCKET newConnection;
	std::cout << "Client is created" << std::endl;
	std::cout << "Press any key to connect to server";
	std::cin.get( );
	newConnection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(newConnection, (SOCKADDR*)&addr, sizeof(addr))) {
		pnautils::throwWSAError("Connection to server");
	}
	std::cout << "Connected to server" << std::endl;
#ifdef _DEBUG
	std::cout << "Press any key to exit...";
	std::cin.get( );
#endif // _DEBUG
}
