#ifndef GAME_H
#define GAME_H

#include <string>

class ChessBoard;

class Game {
	std::string game_mode;

	public:
		void Start(ChessBoard* game_board);
};

#endif