#ifndef SHOGI_KING_H
#define SHOGI_KING_H

#include "pieces/piece.h"

class ShogiKing : public Piece {

	static const int NUM_DIR = 8;
	int dir[NUM_DIR][2] = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
		{1, 1},
		{-1, -1},
		{-1, 1},
		{1, -1},
	};

	public:
	
		ShogiKing(Board* board, const std::string& loc, char player) : Piece{board, loc, KING, player} {}

		bool IsKing() const override { return true; }
		
		int Priority() const override { return Piece::KING_RANK; }

		bool CanPromote() override { return move_count > 0; }
		
		Iterator begin() override {
			auto iter = Iterator{std::make_shared<JumpIterator<ShogiKing::NUM_DIR>>(board, loc, dir, player == BLACK ? 1 : -1)};
			++iter;
			return iter;
		}
};

#endif