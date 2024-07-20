#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "iterators/rook_iterator.h"

class Rook : public Piece {
	public:
	Rook(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, ROOK, player} {}

	Rook(const Piece& other) : Piece{other} {
		name = ROOK;
	}

	bool IsRook() override { return true; }

	Iterator begin() override {
		return Iterator{std::make_shared<RookIterator>(chess_board, loc)};
	}
	Iterator begin(const std::string& loc) override {
		return Iterator{std::make_shared<RookIterator>(chess_board, loc)};
	}
	Iterator end() override {
		return Iterator{std::make_shared<RookIterator>(chess_board, "  ")};
	}
};

#endif