#include "rook_iterator.h"
#include "board.h"

void RookIterator::operator++() {
	std::string next_loc = cloc;
	if (board->Empty(cloc) || cloc == sloc) {
		next_loc[0] += dir[cur_dir][0];
		next_loc[1] += dir[cur_dir][1];
		if (board->InBound(next_loc)) {
			cloc = next_loc;
			return;
		}
	}
	while (++cur_dir < NUM_DIR) {
		next_loc = sloc;
		next_loc[0] += dir[cur_dir][0];
		next_loc[1] += dir[cur_dir][1];
		if (board->InBound(next_loc)) {
			cloc = next_loc;
			return;
		}
	}
	board = nullptr;
}