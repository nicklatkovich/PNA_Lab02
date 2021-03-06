#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <string>

namespace pnautils {
	std::string getErrorMsgText(int code);
	void throwWSAError(std::string process);
	SOCKADDR_IN startSession( );
}

namespace pnautils {
	std::string getErrorMsgText(int code) {
		std::string msgText;
		switch (code) {
			case WSAEINTR:
				msgText = "WSAEINTR";
				break;
			case WSAEACCES:
				msgText = "WSAEACCES";
				break;
				// TODO: process all errors
			case WSASYSCALLFAILURE:
				msgText = "WSASYSCALLFAILURE";
				break;
			default:
				msgText = "Unknown error";
				break;
		};
		return msgText;
	}
	void throwWSAError(std::string process) {
		throw std::exception(("Error at " + process + ": " + getErrorMsgText(WSAGetLastError( ))).c_str( ));

	}
	SOCKADDR_IN startSession( ) {
		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
			pnautils::throwWSAError("Startup");
		}
		SOCKADDR_IN addr;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(4814);
		addr.sin_family = AF_INET;
		return addr;
	}
}
