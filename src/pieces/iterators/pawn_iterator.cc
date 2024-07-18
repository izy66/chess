#include "pawn_iterator.h"
#include "board.h"

void PawnIterator::operator++() {
	int player_dir = board->GetPiecePlayer(sloc) == WHITE ? 1 : -1;
	bool found_next = false;
	while (cur_dir < NUM_DIR && !found_next) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0];
		cloc[1] += dir[cur_dir][1] * player_dir; // white pawn moves up, black pawn moves down
		if (board->InBound(cloc) && ((dir[cur_dir][0] == 0 && board->Empty(cloc)) || (dir[cur_dir][0] != 0 && (!board->Empty(cloc) || board->IsEnPassant(sloc, cloc))))) {
			found_next = true;
		}
		++cur_dir;
	}
	// can pawn make two-square initiation move?
	if (cur_dir == NUM_DIR && !found_next && !board->HasItMoved(sloc)) {
		cloc = sloc;
		cloc[1] += 2 * player_dir;
		std::string up_loc = sloc;
		up_loc[1] += player_dir;
		if (board->InBound(cloc) && board->Empty(cloc) && board->Empty(up_loc)) {
			found_next = true;
		}
		++cur_dir;
	}
	if (!found_next) board = nullptr;
}