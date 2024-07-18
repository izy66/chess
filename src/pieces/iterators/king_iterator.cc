#include "king_iterator.h"
#include "board.h"

void KingIterator::operator++() {
	bool found_step = false;
	while (cur_dir < NUM_DIR && !found_step) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0];
		cloc[1] += dir[cur_dir][1];
		++cur_dir;
		if (board->InBound(cloc)) {
			found_step = true;
		}
	}
	while (!found_step && cas_dir < CAS_DIR && !board->Checked()) {
		cloc = sloc;
		cloc[0] += castle_dir[cas_dir][0];
		cloc[1] += castle_dir[cas_dir][1];
		found_step = board->IsCastling(sloc, cloc);
		++cas_dir;
	}
	if (!found_step) board = nullptr;
}