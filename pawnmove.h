#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "move.h"

class PawnMove : public Move {
	public:
		PawnMove(std::string& from, std::string& to) : Move{from, to} {}
		bool MakeMoveOn(Board*) override;
		void Undo(Board*) override {}
};

#endif