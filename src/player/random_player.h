#ifndef COMPUTER_LEVEL_1
#define COMPUTER_LEVEL_1

#include "computer_player.h"

class RandomPlayer : public ComputerPlayer {
	public:
		RandomPlayer(char);
		bool MakeMove(Board*) override;
};

#endif