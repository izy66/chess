#ifndef COMPUTER_LEVEL_4
#define COMPUTER_LEVEL_4

#include <memory>

class Board;
class ComputerPlayer;
class AbstractMove;

class ComputerLevel4 {

	Board *board;
	std::string best_from, best_move;
	char player, opponent;
	
	int alpha_beta_max(ComputerPlayer* comp_player, int level, int alpha, int beta);
	int alpha_beta_min(ComputerPlayer* comp_player, int level, int alpha, int beta);

	public:

		ComputerLevel4(Board* board) : board{board} {}
	
		void MakeMove(ComputerPlayer* player);
};

#endif