#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "iterators/slide_iterator.h"

class Bishop : public Piece {

	static const int NUM_DIR = 4;
	int dir[NUM_DIR][2] = {
		{1, 1},
		{-1, 1},
		{-1, -1},
		{1, -1}
	};

	public:
		Bishop(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, BISHOP, player} {}

		Bishop(const Piece& other) : Piece{other} {
			name = BISHOP;
		}

		int Priority() const override { return Piece::BISHOP_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<SlideIterator<Bishop::NUM_DIR>>(chess_board, loc, dir)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<SlideIterator<Bishop::NUM_DIR>>(chess_board, "  ", dir)};
		}
};

#endif