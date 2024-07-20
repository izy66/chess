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

		Iterator begin() override {
			return Iterator{std::make_shared<BishopIterator>(chess_board, loc)};
		}
		Iterator begin(const std::string& loc) override {
			return Iterator{std::make_shared<BishopIterator>(chess_board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<BishopIterator>(chess_board, "  ")};
		}
};

#endif