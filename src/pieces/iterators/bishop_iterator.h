#ifndef BISHOP_ITERATOR_H
#define BISHOP_ITERATOR_H

#include "iterator.h"

class BishopIterator : public PieceIterator {
	static const int NUM_DIR = 4;
	int dir[NUM_DIR][2] = {
		{1, 1},
		{-1, 1},
		{-1, -1},
		{1, -1}
	};
	int cur_dir;

	public:
		BishopIterator(Board* board, const std::string& loc) : PieceIterator{board, loc}, cur_dir{0} {}
		virtual void operator++() override;
};

#endif