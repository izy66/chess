#ifndef SHOGI_HORSE_H
#define SHOGI_HORSE_H

#include "pieces/piece.h"

class ShogiHorse : public Piece {
	
	static const int NUM_DIR_JUMP = 4;
	int dir_jump[NUM_DIR_JUMP][2] = {
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0},
	};

	static const int NUM_DIR_SLIDE = 4;
	int dir_slide[NUM_DIR_SLIDE][2] = {
		{1, 1},
		{-1, 1},
		{1, -1},
		{-1, -1}
	};

	public:
	
		ShogiHorse(Board* board, const std::string& loc, char player) : Piece{board, loc, HORSE, player} {}

		ShogiHorse(const Piece& other) : Piece{other} {
			name = HORSE;
		}

		int Priority() const override { return Piece::HORSE_RANK; }

		bool CanPromote() override { return move_count > 0; }
		
		Iterator begin() override {
			auto iter = Iterator{std::make_shared<JumpIterator<ShogiHorse::NUM_DIR_JUMP>>(board, loc, dir_jump, player == BLACK ? 1 : -1), std::make_shared<SlideIterator<ShogiHorse::NUM_DIR_SLIDE>>(board, loc, dir_slide, player == BLACK ? 1 : -1)};
			++iter;
			return iter;
		}
};

#endif