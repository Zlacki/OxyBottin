#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <array>
#include "model/Mob.hpp"

namespace RSC {
	class Client {
	private:
		std::array<Mob, 500> npcs;
	public:
		std::array<Mob, 500> &getNPCs();
		void connect(std::string, std::string, uint8_t);
	};
}

#endif
