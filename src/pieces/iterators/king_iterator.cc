#include "king_iterator.h"
#include "board.h"

void KingIterator::operator++() {
	bool found_step = false;
	while (cur_dir < NUM_DIR && !found_step) {
		cloc = sloc;
		cloc[0] += dir[cur_dir][0];
		cloc[1] += dir[cur_dir][1];
		++cur_dir;
		if (board->in_bound(cloc)) {
			found_step = true;
		}
	}
	while (!found_step && cas_dir < CAS_DIR && !board->Checked()) {
		cloc = sloc;
		cloc[0] += castle_dir[cas_dir][0];
		cloc[1] += castle_dir[cas_dir][1];
		// if (board->in_bound(cloc)) {
		// 	std::string rook_dest = sloc;
		// 	rook_dest[0] += castle_dir[cas_dir][0] / 2;
		// 	std::string rook_loc = rook_dest;
		// 	while (board->in_bound(rook_loc)) {
		// 		char name = toupper(board->GetPieceName(rook_dest));
		// 		if (!board->Empty(rook_dest) && name != ROOK) break;
		// 		if (name == ROOK) {
		// 			if (!board->HasItMoved(sloc) && !board->HasItMoved(rook_loc)) {
		// 				found_step = true;
		// 			}
		// 			break;
		// 		}
		// 		rook_loc[0] += castle_dir[cas_dir][0] / 2;
		// 	}
		// }
		found_step = board->IsCastling(sloc, cloc);
		++cas_dir;
	}
	if (!found_step) board = nullptr;
}