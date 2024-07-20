#ifndef COMPUTER_LEVEL_2
#define COMPUTER_LEVEL_2

class Board;
class ComputerPlayer;

class BeginnerPlayer {
	Board* chess_board;
	char player;
	public:
		BeginnerPlayer(Board* chess_board, char player) : chess_board{chess_board}, player{player} {}
	
		void MakeMove(ComputerPlayer* player);
};

#endif