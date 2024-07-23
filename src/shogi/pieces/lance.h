#ifndef SHOGI_LANCE_H
#define SHOGI_LANCE_H

#include "pieces/piece.h"

class ShogiLance : public Piece {
	
	static const int NUM_DIR = 1;
	int dir_slide[NUM_DIR][2] = {
		{0, 1},
	};

	public:
	
		ShogiLance(Board* board, const std::string& loc, char player) : Piece{board, loc, LANCE, player} {}

		int Priority() const override { return Piece::LANCE_RANK; }

		bool CanPromote() override { return move_count > 0; }
		bool CanDrop() override;

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<SlideIterator<ShogiLance::NUM_DIR>>(board, loc, dir_slide, player == BLACK ? 1 : -1)};
			++iter;
			return iter;
		}
};

#endif