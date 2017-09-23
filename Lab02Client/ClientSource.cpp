#include <iostream>
#include "Utils.h"

void main( ) {
	SOCKADDR_IN addr = pnautils::startSession( );
	SOCKET newConnection;
	std::cout << "Client is created" << std::endl;
	std::cout << "Press any key to connect to server";
	std::cin.get( );
	newConnection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(newConnection, (SOCKADDR*)&addr, sizeof(addr))) {
		pnautils::throwWSAError("Connection to server");
	}
	std::cout << "Connected to server" << std::endl;
	while (true) {
		std::cout << "Select command:" << std::endl;
		std::cout << "1. Send 1 message" << std::endl;
		std::cout << "2. Send N messages" << std::endl;
		std::cout << "3. Disconnect" << std::endl;
		std::string command;
		std::cin >> command;
		char message[256] = "";
		if (command == "1") {
			std::cout << "Enter message: " << std::endl;
			std::cin.ignore( );
			std::cin.getline(message, sizeof(message));
			send(newConnection, message, sizeof(message), NULL);
			recv(newConnection, message, sizeof(message), NULL);
		} else if (command == "2") {
			std::cout << "Enter message: " << std::endl;
			std::cin.ignore( );
			std::cin.getline(message, sizeof(message));
			while (true) {
				try {
					std::cout << "Enter the number of times to send message to server: " << std::endl;
					char numStr[6];
					//std::cin.ignore( );
					std::cin.getline(numStr, sizeof(numStr));
					int num = atoi(numStr);
					for (int i = 0; i < num; i++) {
						std::string newMessage = message;
						newMessage += " ";
						newMessage += std::to_string(i);
						send(newConnection, newMessage.c_str( ), newMessage.length( ) + 1, NULL);
						char recvMessage[256];
						recv(newConnection, recvMessage, sizeof(recvMessage), NULL);
					}
					break;
				} catch (...) {

				}
			}
		} else if (command == "3") {
			send(newConnection, message, 256, NULL);
			break;
		}
	}
#ifdef _DEBUG
	std::cout << "Press any key to exit...";
	std::cin.get( );
#endif // _DEBUG
	closesocket(newConnection);
	WSACleanup( );
}
