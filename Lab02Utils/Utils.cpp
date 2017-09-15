#include "Utils.h"
#include <exception>

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
	};
	void throwWSAError(std::string process) {
		throw std::exception(("Error at " + process + ": " + getErrorMsgText(WSAGetLastError( ))).c_str( ));
	}
}

void main( ) {

}
