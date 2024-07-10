#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "iterators/queen_iterator.h"

class Queen : public Piece {
	public:
		Queen(char player) : Piece{static_cast<char>(player == WHITE ? toupper(QUEEN) : tolower(QUEEN)), player} {}
		void Move(const std::string&) override {}

		Iterator begin(Board* board, const std::string& loc) override {
			return Iterator{std::make_shared<QueenIterator>(board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<QueenIterator>(nullptr, "x")};
		}
};

#endif