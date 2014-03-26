#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include "RSC/Client.hpp"
#include "RSC/model/Mob.hpp"

using namespace RSC;

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET proxySocket = INVALID_SOCKET;
	SOCKET connectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int i = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(i != 0) {
		std::cout << "Network startup failed." << std::endl;
		return EXIT_FAILURE;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	i = getaddrinfo(NULL, "6991", &hints, &result);
	if(i != 0) {
		std::cout << "Network startup failure." << std::endl;
		WSACleanup();
		return EXIT_FAILURE;
	}

	proxySocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(proxySocket == INVALID_SOCKET) {
		std::cout << "Network startup failure." << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return EXIT_FAILURE;
	}

	u_long mode = 1;
	i = ioctlsocket(proxySocket, FIONBIO, &mode);
	if(i == SOCKET_ERROR) {
		std::cout << "Network startup failure." << std::endl;
		closesocket(proxySocket);
		WSACleanup();
		return EXIT_FAILURE;
	}

	i = bind(proxySocket, result->ai_addr, (int)result->ai_addrlen);
	if(i == SOCKET_ERROR) {
		std::cout << "Network startup failure." << std::endl;
		freeaddrinfo(result);
		closesocket(proxySocket);
		WSACleanup();
		return EXIT_FAILURE;
	}

	freeaddrinfo(result);

	i = listen(proxySocket, SOMAXCONN);
	if(i == SOCKET_ERROR) {
		std::cout << "Network startup failure." << std::endl;
		closesocket(proxySocket);
		WSACleanup();
		return EXIT_FAILURE;
	}

	std::cout << "Awaiting incoming connections..." << std::endl;

	for(;;) {
		connectSocket = accept(proxySocket, NULL, NULL);

		if (connectSocket != INVALID_SOCKET) {
			char value = 1;
			setsockopt(connectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
			std::cout << "Recieved incoming connection, forwarding...";
		}
		/* todo: forward connection to RSCE servers */
	}

	Client client;
	return EXIT_SUCCESS;
}
