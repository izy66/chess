#ifndef KING_ITERATOR_H
#define KING_ITERATOR_H

#include "iterator.h"

class KingIterator : public PieceIterator {
	static const int NUM_DIR = 10;
	static const int CAS_DIR = 2;
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
	int castle_dir[CAS_DIR][2] = {
		{2, 0},
		{-2, 0}
	};
	int cur_dir, cas_dir;

	public:
		KingIterator(Board* board, const std::string& loc) : PieceIterator{board, loc}, cur_dir{0}, cas_dir{0} {}
		virtual void operator++() override;
};

#endif