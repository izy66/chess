#ifndef ABSTRACT_MOVE_H
#define ABSTRACT_MOVE_H

#include <string>

class Board;
class Piece;

class AbstractMove {

	friend class Piece;

	public:
	
		virtual void MakeMoveOn(Board*) = 0; // return 1 if execution is successful
		virtual void Undo() = 0; // any valid execution can be undone
	
		virtual ~AbstractMove() = default;
};

#endif