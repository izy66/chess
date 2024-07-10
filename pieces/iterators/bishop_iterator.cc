#include "bishop_iterator.h"
#include "board.h"

void BishopIterator::operator++() {
	std::string next_loc = cloc;
	if (board->Empty(cloc)) {
		next_loc[0] += dir[cur_dir][0];
		next_loc[1] += dir[cur_dir][1];
		if (board->in_bound(next_loc)) {
			cloc = next_loc;
			return;
		}
	} else {
		while (++cur_dir < NUM_DIR) {
			next_loc = sloc;
			next_loc[0] += dir[cur_dir][0];
			next_loc[1] += dir[cur_dir][1];
			if (board->in_bound(next_loc)) {
				cloc = next_loc;
				return;
			}
		}
	}
	board = nullptr;
}