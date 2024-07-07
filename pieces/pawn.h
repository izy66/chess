#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
	public:
	Pawn(char col) : Piece{col == WHITE ? 'P' : 'p', col} {}
	void Move(const std::string&) override {}
};

#endif