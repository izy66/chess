#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "iterators/bishop_iterator.h"

class Bishop : public Piece {
	public:
		Bishop(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, BISHOP, player} {}

		Bishop(const Piece& other) : Piece{other} {
			name = BISHOP;
		}

		int Priority() const override { return Piece::BISHOP_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<BishopIterator>(chess_board, loc)};
			++iter;
			return iter;
		}
		// Iterator begin(const std::string& loc) override {
		// 	auto iter = Iterator{std::make_shared<BishopIterator>(chess_board, loc)};
		// 	++iter;
		// 	return iter;
		// }
		Iterator end() override {
			return Iterator{std::make_shared<BishopIterator>(chess_board, "  ")};
		}
};

#endif