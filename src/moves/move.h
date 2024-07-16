#ifndef MOVE_H
#define MOVE_H

#include "board.h"
#include <string>

class Board;

class Move {
	protected:
		Board *chess_board;
		std::string from, to;
		bool first_move, captured;
	public:
		Move(std::string& from, std::string& to);
		virtual bool MakeMoveOn(Board*); // return 1 if execution is successful
		virtual bool Undo(Board*) { return 1; } // any valid execution can be undone
		virtual ~Move() {}
		// std::string From() const { return from; }
		// std::string To() const { return to; }
		Move(Move& other) {
			from = other.from;
			to = other.to;
			first_move = other.first_move;
			captured = other.captured;
		}
};

#endif