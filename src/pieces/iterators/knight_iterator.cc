#include "knight_iterator.h"
#include "board.h"

void KnightIterator::operator++() {
	// search for next valid move
	while (cur_dir < NUM_DIR) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0];
		cloc[1] += dir[cur_dir][1];
		++cur_dir;
		if (board->InBound(cloc)) {
			return;
		}
	}
	// no moves left
	board = nullptr;
}