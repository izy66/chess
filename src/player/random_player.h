#ifndef COMPUTER_LEVEL_1
#define COMPUTER_LEVEL_1

#include "computer_player.h"

class RandomPlayer final : public ComputerPlayer {
	public:
		RandomPlayer(Board*, char);
		
		void MakeMove() override;
};

#endif