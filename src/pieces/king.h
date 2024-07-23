#ifndef KING_H
#define KING_H

#include "piece.h"
#include "iterators/jump_iterator.h"

class King : public Piece {

	static const int NUM_DIR = 10;
	int dir[NUM_DIR][2] = {
		{1, 0},
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{-1, -1},
		{0, -1},
		{1, -1},
		{2, 0},
		{-2, 0}
	};

	public:
	
		King(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, KING, player} {}

		bool IsKing() const override { return true; }
		bool IsCastling(const std::string&) const override;
		
		int Priority() const override { return Piece::KING_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<JumpIterator<King::NUM_DIR>>(chess_board, loc, dir, player == WHITE ? 1 : -1)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<JumpIterator<King::NUM_DIR>>(chess_board, "  ", dir, player == WHITE ? 1 : -1)};
		}
};

#endif