#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "chessboard.h"
#include "decisiontree.h"
#include <memory>
#include <iostream>
#include <stack>

class Controller {
	ChessBoard* chess_board;

	public:
		Controller(ChessBoard* board) : chess_board{board} {}
		~Controller();

		void StartGame(); // start game flow
		void RunGame(); // run a match until ctrl + D
		void Setup(); // setup mode

		void GameOver();
};

#endif