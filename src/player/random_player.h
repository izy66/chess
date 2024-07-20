#ifndef COMPUTER_LEVEL_1
#define COMPUTER_LEVEL_1

class Board;
class ComputerPlayer;

class RandomPlayer {
	Board* chess_board;
	char player;

	public:
		RandomPlayer(Board*, char);
		
		void MakeMove(ComputerPlayer* player);
};

#endif