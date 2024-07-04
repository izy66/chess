#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
	public:
		King(char col) : Piece{'k', col} {}
		void Move(const std::string&) override;
};

#endif