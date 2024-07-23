#ifndef SHOGI_GOLD_GENERAL_H
#define SHOGI_GOLD_GENERAL_H

#include "pieces/piece.h"

class ShogiGold : public Piece {
	
	static const int NUM_DIR_JUMP = 6;
	int dir_jump[NUM_DIR_JUMP][2] = {
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{1, 0},
		{0, -1}
	};

	public:
	
		ShogiGold(Board* board, const std::string& loc, char player) : Piece{board, loc, GOLD, player} {}

		ShogiGold(const Piece& other) : Piece{other} {
			name = GOLD;
		}

		int Priority() const override { return Piece::GOLD_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<JumpIterator<ShogiGold::NUM_DIR_JUMP>>(board, loc, dir_jump, player == BLACK ? 1 : -1)};
			++iter;
			return iter;
		}
};

#endif