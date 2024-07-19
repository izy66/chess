#ifndef MOVE_H
#define MOVE_H

#include "board.h"
#include <string>

class Board;

class Move {
	protected:
		Board *chess_board;
		std::string from, to;
		bool first_move, captured, promotion;
	public:
		Move(const std::string& from, const std::string& to);
		virtual void MakeMoveOn(Board*); // return 1 if execution is successful
		virtual void Undo(Board*) {} // any valid execution can be undone
		virtual ~Move() { Undo(chess_board); }
		bool IsPromotion() { return promotion; }

		Move(Move& other) {
			chess_board = other.chess_board;
			from = other.from;
			to = other.to;
			first_move = other.first_move;
			captured = other.captured;
		}
};

#endif