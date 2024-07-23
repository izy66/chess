#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "iterators/jump_iterator.h"

class Knight : public Piece {

	static const int NUM_DIR = 8;
	int dir[NUM_DIR][2] = {
		{2, 1},
		{1, 2},
		{-1, 2},
		{-2, 1},
		{-2, -1},
		{-1, -2},
		{1, -2},
		{2, -1}
	};

	public:
		
		Knight(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, KNIGHT, player} {}

		Knight(const Piece& other) : Piece{other} {
			name = KNIGHT;
		}

		int Priority() const override { return Piece::KNIGHT_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<JumpIterator<Knight::NUM_DIR>>(chess_board, loc, dir, player == WHITE ? 1 : -1)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<JumpIterator<Knight::NUM_DIR>>(chess_board, "  ", dir, player == WHITE ? 1 : -1)};
		}
};

#endif