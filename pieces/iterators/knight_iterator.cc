#include "knight_iterator.h"
#include "board.h"

void KnightIterator::operator++() {
	while (cur_dir < NUM_DIR) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0];
		cloc[1] += dir[cur_dir][1];
		++cur_dir;
		if (board->in_bound(cloc)) {
			return;
		}
	}
	board = nullptr;
}