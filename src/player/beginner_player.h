#ifndef COMPUTER_LEVEL_2
#define COMPUTER_LEVEL_2

#include "advanced_computer.h"

class BeginnerPlayer : public AdvancedComputer {
	public:
		BeginnerPlayer(std::shared_ptr<Player> base_player, char player) : AdvancedComputer{base_player, player} {}
		bool MakeMove(Board*) override;
};

#endif