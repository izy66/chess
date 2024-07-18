#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class HumanPlayer : public Player {
	std::string from, to, promotion;
	bool take_action(Board*) override;
	public:
		HumanPlayer(char);
		HumanPlayer(HumanPlayer&);
		bool MakeMove(Board*) override;
		~HumanPlayer();
};

#endif