#include "Client.hpp"

namespace RSC {
	std::array<Mob, 500> &Client::getNPCs() {
		return this->npcs;
	}

	void Client::connect(std::string username, std::string password, uint8_t world) {
		/* todo */
		return;
	}
};
