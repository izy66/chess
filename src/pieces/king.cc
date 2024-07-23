#include "king.h"
#include "board.h"

bool King::IsCastling(const std::string& to) const {
	if (board->Checked()) return false; // can't castle if not king or king in check
	if (HasMoved()) return false; // can't castle if king has moved
	if (abs(to[0] - loc[0]) != 2 || to[1] != loc[1]) return false;
	int castle_dir = (to[0] - loc[0]) / 2;
	std::string rook_loc = to;
	std::string rook_dest = loc;
	rook_dest[0] += castle_dir;
	if ((*board)[rook_loc] != nullptr) return false; // can't castle if there are pieces on the way
	while (board->InBound(rook_loc)) {
		std::unique_ptr<Piece>& rook = (*board)[rook_loc];
		if (rook != nullptr && !rook->IsRook()) return false; // can't castle if there are pieces on the way
		if (rook != nullptr) {
			if (!rook->HasMoved()) {
				return true;
			}
			return false;
		}
		rook_loc[0] += castle_dir;
	}
	return false;
}