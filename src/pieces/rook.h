#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "iterators/rook_iterator.h"

class Rook : public Piece {
	public:
	Rook(char col) : Piece{col == WHITE ? 'R' : 'r', col} {}

	Iterator begin(Board* board, const std::string& loc) override {
		return Iterator{std::make_shared<RookIterator>(board, loc)};
	}
	Iterator end() override {
		return Iterator{std::make_shared<RookIterator>(nullptr, "x")};
	}
};

#endif