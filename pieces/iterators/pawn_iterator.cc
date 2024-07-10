#include "pawn_iterator.h"
#include "board.h"

void PawnIterator::operator++() {
	int player_dir = board->GetPieceName(sloc) == WHITE ? 1 : -1;
	while (cur_dir < NUM_DIR) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0] * player_dir;
		cloc[1] += dir[cur_dir][1] * player_dir;
		++cur_dir;
		if (board->in_bound(cloc) && (dir[cur_dir][0] == 0 || !board->Empty(cloc))) {
			return;
		}
	}
	board = nullptr;
}