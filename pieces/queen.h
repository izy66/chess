#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
	public:
	Queen(char col) : Piece{'q', col} {}
	void Move(const std::string&) override {}
};

#endif