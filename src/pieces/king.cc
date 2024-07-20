#include "king.h"
#include "board.h"

bool King::CanMove(const std::string& to) {
	if (chess_board->GetPiecePlayer(to) == player || chess_board->CanBeSeen(to, player)) return 0;
	Piece::Iterator move = begin(loc);
	++move;
	for (; move != end(); ++move) {
		if (*move == to) return 1;
	}
	return 0;
}

bool King::CanCover(const std::string& to) {
	if (chess_board->CanBeSeen(to, player)) return 0;
	Piece::Iterator move = begin(loc);
	++move;
	for (; move != end(); ++move) {
		if (*move == to) return 1;
	}
	return 0;
}

bool King::IsCastling(const std::string& to) const {
	if (chess_board->Checked()) return 0; // can't castle if not king or king in check
	if (HasMoved()) return 0; // can't castle if king has moved
	if (abs(to[0] - loc[0]) != 2 || to[1] != loc[1]) return 0;
	int castle_dir = (to[0] - loc[0]) / 2;
	std::string rook_loc = to;
	std::string rook_dest = loc;
	rook_dest[0] += castle_dir;
	if ((*chess_board)[rook_loc] != nullptr) return 0; // can't castle if there are pieces on the way
	while (chess_board->InBound(rook_loc)) {
		auto rook = (*chess_board)[rook_loc];
		if (rook != nullptr && !rook->IsRook()) return 0; // can't castle if there are pieces on the way
		if (rook != nullptr) {
			if (!rook->HasMoved()) {
				return 1;
			}
			return 0;
		}
		rook_loc[0] += castle_dir;
	}
	return 0;
}