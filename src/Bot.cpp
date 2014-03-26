#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "RSC/Client.hpp"
#include "RSC/model/Mob.hpp"

using namespace RSC;

int main(int argc, char *argv[]) {
	int sock1 = socket(AF_INET, SOCK_STREAM, 0);
	if(sock1 < 0) {
		std::cout << "Proxy socket could not be created." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Proxy socket created." << std::endl;

	int sock2 = socket(AF_INET, SOCK_STREAM, 0);
	if(sock2 < ) {
		std::cout << "Remote server socket could not be created." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Remote server socket created." << std::endl;

	struct sockaddr_in server, localgr, proxy;

	proxy.sin_family = AF_INET;
	proxy.sin_addr.s_addr = htonl(INADDR_ANY);
	proxy.sin_port = htons(43594);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_aton("
	server.sin_port = htons(43594);

	Client client;
	/* todo: everything */
	return EXIT_SUCCESS;
}
