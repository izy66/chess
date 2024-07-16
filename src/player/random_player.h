#ifndef COMPUTER_LEVEL_1
#define COMPUTER_LEVEL_1

#include "player.h"

class RandomPlayer : public Player {
	public:
		RandomPlayer(Board*, char);
		bool MakeMove() override;
		bool Undo() override { return 1; }
};

#endif