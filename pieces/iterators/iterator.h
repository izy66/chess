#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <iostream>

class Board;

class PieceIterator {
	protected:
		Board* board;
		std::string sloc, cloc;
		int cur_dir;
	public:
		PieceIterator(Board* board, const std::string& loc) : board{board}, sloc{loc}, cloc{loc}, cur_dir{0} {}
		virtual ~PieceIterator() {}
		virtual bool operator!=(PieceIterator& other) {
			return board != nullptr && (board != other.board || sloc != other.sloc || cloc != other.cloc);
		}
		virtual void operator++() = 0;
		virtual std::string operator*() { return cloc; }
};

#endif 