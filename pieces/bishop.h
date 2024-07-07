#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
	public:
		Bishop(char col) : Piece{col == WHITE ? 'B' : 'b', col} {}
		void Move(const std::string&) override {}
};

#endif