#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "iterators/bishop_iterator.h"

class Bishop : public Piece {
	public:
		Bishop(char player) : Piece{static_cast<char>(player == WHITE ? toupper(BISHOP) : tolower(BISHOP)), player} {}
		void Move(const std::string&) override {}

		Iterator begin(Board* board, const std::string& loc) override {
			return Iterator{std::make_shared<BishopIterator>(board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<BishopIterator>(nullptr, "x")};
		}
};

#endif