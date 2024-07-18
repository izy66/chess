#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include "player.h"

class Board;

class ComputerPlayer : public Player {
	protected:
		bool take_action(Board*) override;
	public:
		ComputerPlayer(char player) : Player{player} { is_human = false; }
		virtual ~ComputerPlayer() {}
		virtual bool MakeMove(Board*) override = 0;
};

#endif