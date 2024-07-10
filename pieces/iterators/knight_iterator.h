#ifndef KNIGHT_ITERATOR_H
#define KNIGHT_ITERATOR_H

#include "iterator.h"

class KnightIterator : public PieceIterator {
	static const int NUM_DIR = 8;
	const int dir[NUM_DIR][2] = {
		{2, 1},
		{1, 2},
		{-1, 2},
		{-2, 1},
		{-2, -1},
		{-1, -2},
		{1, -2},
		{2, -1}
	};
	int cur_dir;

	public:
		KnightIterator(Board* board, const std::string& loc) : PieceIterator{board, loc}, cur_dir{0} {}
		virtual void operator++() override;
};

#endif