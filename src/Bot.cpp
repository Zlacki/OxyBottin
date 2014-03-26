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
	if(sock2 < 0) {
		std::cout << "Remote server socket could not be created." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Remote server socket created." << std::endl;

	struct sockaddr_in server, localgr, proxy;

	proxy.sin_family = AF_INET;
	proxy.sin_addr.s_addr = htonl(INADDR_ANY);
	proxy.sin_port = htons(43591);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_aton("69.42.219.82", &server.sin_addr);
	server.sin_port = htons(43591);

	int state = bind(sock1, (struct sockaddr *) &proxy, sizeof(proxy));
	if(state < 0) {
		std::cout << "Bind error, please close all bot windows." << std::endl;
		return EXIT_FAILURE;
	}
	listen(sock1, 5);
	std::cout << "Ready for incoming connections." << std::endl;

	int len = sizeof(localgr);
	int sda = accept(sock1, (struct sockaddr *) &localgr, (socklen_t *) &localgr);
	if(sda < 0) {
		std::cout << "Error connecting to client." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Forwarding connection...";

	if((connect(sock2, (struct sockaddr *) &server, sizeof(server))) < 0) {
		std::cout << "Failed." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Connection established" << std::endl;

	Client client;
	/* todo: everything */
	return EXIT_SUCCESS;
}
