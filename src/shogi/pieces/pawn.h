#ifndef SHOGI_PAWN_H
#define SHOGI_PAWN_H

#include "pieces/piece.h"

class ShogiPawn : public Piece {

	static const int NUM_DIR = 1;
	int dir[NUM_DIR][2] = {
		{0, 1}
	};

	public:
	
		ShogiPawn(Board* board, const std::string& loc, char player) : Piece{board, loc, PAWN, player} {}
		
		int Priority() const override { return Piece::PAWN_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<JumpIterator<ShogiPawn::NUM_DIR>>(board, loc, dir, player == BLACK ? 1 : -1)};
			++iter;
			return iter;
		}
};

#endif