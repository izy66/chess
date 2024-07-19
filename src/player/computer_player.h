#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include "player.h"

class Board;

class ComputerPlayer : public Player {
	protected:
	public:
		ComputerPlayer(Board* chess_board, char player) : Player{chess_board, player} { is_human = false; }
		
		virtual ~ComputerPlayer() {}

		void TakeAction() override;
		void MakeMove() override = 0;
};

#endif