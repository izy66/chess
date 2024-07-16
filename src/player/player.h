#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <stack>

class Board;
class Move;
class Parser;

class Player {
	protected:
		Board *chess_board;
		char player;
		std::unique_ptr<Parser> parser;
		std::stack<std::unique_ptr<Move>> moves;

	public:
		Player(Board* chess_board, char player);
		virtual ~Player();
		virtual bool MakeMove() = 0;
		virtual bool Undo();
};

#endif