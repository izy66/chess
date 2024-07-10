#ifndef ROOK_ITERATOR_H
#define ROOK_ITERATOR_H

#include "iterator.h"

class RookIterator : public PieceIterator {
	static const int NUM_DIR = 4;
	int dir[NUM_DIR][2] = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	};
	int cur_dir;

	public:
		RookIterator(Board* board, const std::string& loc) : PieceIterator{board, loc}, cur_dir{0} {}
		virtual void operator++() override;
};

#endif 