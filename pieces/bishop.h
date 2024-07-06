#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
	public:
		Bishop(char col) : Piece{'b', col} {}
		void Move(const std::string&) override {}
};

#endif