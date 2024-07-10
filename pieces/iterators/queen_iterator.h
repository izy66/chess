#ifndef QUEEN_ITERATOR_H
#define QUEEN_ITERATOR_H

#include "iterator.h"

class QueenIterator : public PieceIterator {
	static const int NUM_DIR = 8;
	int dir[NUM_DIR][2] = {
		{1, 0},
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{-1, -1},
		{0, -1},
		{1, -1}
	};
	int cur_dir;

	public:
		QueenIterator(Board* board, const std::string& loc) : PieceIterator{board, loc}, cur_dir{0} {}
		virtual void operator++() override;
};

#endif 