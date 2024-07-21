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

	bool IsRook() const override { return true; }

	int Priority() const override { return Piece::ROOK_RANK; }

	Iterator begin() override {
		auto iter = Iterator{std::make_shared<RookIterator>(chess_board, loc)};
		++iter;
		return iter;
	}
	// Iterator begin(const std::string& loc) override {
	// 	auto iter = Iterator{std::make_shared<RookIterator>(chess_board, loc)};
	// 	++iter;
	// 	return iter;
	// }
	Iterator end() override {
		return Iterator{std::make_shared<RookIterator>(chess_board, "  ")};
	}
};

#endif