#ifndef MOVE_H
#define MOVE_H

#include "board.h"
#include <string>

class Board;

class Move {
	protected:
		std::string from, to;
		bool first_move, captured;
	public:
		Move(std::string& from, std::string& to, bool first_move = false) : from{from}, to{to}, first_move{first_move}, captured{false} {}
		virtual ~Move() {}
		virtual bool MakeMoveOn(Board*) = 0; // return 1 if execution is successful
		virtual void Undo(Board*) {} // any valid execution can be undone
};

#endif