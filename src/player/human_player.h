#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class HumanPlayer final : public Player {
	std::string from, to, promotion;
	public:
		HumanPlayer(Board*, char);
		~HumanPlayer() {}
		
		void TakeAction() override;
		void MakeMove() override;
};

#endif