#include "king.h"
#include "board.h"

bool King::CanMove(const std::string& to) {
	return chess_board->GetPiecePlayer(to) != player && !chess_board->CanBeSeen(to, player);
}

bool King::CanCover(const std::string& to) {
	// calling Board::CanBeSeen to avoid recursive calls
	if (chess_board->CanBeSeen(to, player)) return false;
	for (const auto& move : *this) {
		if (move == to) return true;
	}
	return false;
}

bool King::IsCastling(const std::string& to) const {
	if (chess_board->Checked()) return false; // can't castle if not king or king in check
	if (HasMoved()) return false; // can't castle if king has moved
	if (abs(to[0] - loc[0]) != 2 || to[1] != loc[1]) return false;
	int castle_dir = (to[0] - loc[0]) / 2;
	std::string rook_loc = to;
	std::string rook_dest = loc;
	rook_dest[0] += castle_dir;
	if ((*chess_board)[rook_loc] != nullptr) return false; // can't castle if there are pieces on the way
	while (chess_board->InBound(rook_loc)) {
		auto rook = (*chess_board)[rook_loc];
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