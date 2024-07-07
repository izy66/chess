#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "move.h"

class PawnMove : public Move {
	public:
		PawnMove(std::string& from, std::string& to, bool first_move = false) : Move{from, to, first_move} {}
		bool MakeMoveOn(ChessBoard*) override;
		void Undo(ChessBoard*) override {}
};

#endif