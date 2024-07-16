#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "iterators/knight_iterator.h"

class Knight : public Piece {
	public:
		Knight(char col) : Piece{col == WHITE ? 'N' : 'n', col} {}

		Iterator begin(Board* board, const std::string& loc) override {
			return Iterator{std::make_shared<KnightIterator>(board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<KnightIterator>(nullptr, "x")};
		}
};

#endif