#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include "move.h"

class KnightMove : public Move {
	public:
		KnightMove(std::string& from, std::string& to) : Move{from, to} {}
		bool MakeMoveOn(ChessBoard*) override;
		void Undo(ChessBoard*) override {}

};

#endif