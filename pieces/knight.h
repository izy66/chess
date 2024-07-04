#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
	public:
	Knight(char col) : Piece{'n', col} {}
	void Move(const std::string&) override {}
};

#endif