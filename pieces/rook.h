#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
	public:
	Rook(char col) : Piece{'r', col} {}
	void Move(const std::string&) override {}
};

#endif