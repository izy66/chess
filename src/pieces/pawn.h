#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "iterators/pawn_iterator.h"

class Pawn : public Piece {
	public:
	Pawn(char col) : Piece{col == WHITE ? 'P' : 'p', col} {}
	void Move(const std::string&) override {}

	Iterator begin(Board* board, const std::string& loc) override {
		return Iterator{std::make_shared<PawnIterator>(board, loc)};
	}
	Iterator end() override {
		return Iterator{std::make_shared<PawnIterator>(nullptr, "x")};
	}	
};

#endif