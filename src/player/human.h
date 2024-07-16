#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Parser;

class HumanPlayer : public Player {
	public:
		HumanPlayer(Board* chess_board, char player);
		bool MakeMove() override;
		HumanPlayer(HumanPlayer& other);
		~HumanPlayer();
};

#endif