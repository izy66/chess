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
		Move(std::string& from, std::string& to);
		virtual bool MakeMoveOn(Board*); // return 1 if execution is successful
		virtual void Undo(Board*) {} // any valid execution can be undone
		virtual ~Move() {}
		// std::string From() const { return from; }
		// std::string To() const { return to; }
};

#endif