#include "king_iterator.h"
#include "board.h"

void KingIterator::operator++() {
	bool found_step = false;
	// search adjacent squares, find valid move
	while (cur_dir < NUM_DIR && !found_step) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0];
		cloc[1] += dir[cur_dir][1];
		++cur_dir;
		if (board->InBound(cloc)) {
			found_step = true;
		}
	}
	// no moves left
	if (!found_step) board = nullptr;
}