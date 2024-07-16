#ifndef KING_H
#define KING_H

#include "piece.h"
#include "iterators/king_iterator.h"

class King : public Piece {
	public:
		King(char col) : Piece{col == WHITE ? 'K' : 'k', col} {}

		Iterator begin(Board* board, const std::string& loc) override {
			return Iterator{std::make_shared<KingIterator>(board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<KingIterator>(nullptr, "x")};
		}
};

#endif