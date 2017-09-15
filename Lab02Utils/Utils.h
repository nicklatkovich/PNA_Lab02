#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <string>

namespace pnautils {
	std::string getErrorMsgText(int code);
	void throwWSAError(std::string process);
}
