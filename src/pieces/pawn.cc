#include "pawn.h"
#include "board.h"

bool Pawn::IsEnPassant(const std::string& to) const {
	if (loc[0] == to[0] || abs(loc[1] - to[1]) > 1) return false;
	std::string en_passant_loc = std::string() + to[0] + loc[1];
	return (*chess_board)[en_passant_loc] != nullptr && (*chess_board)[en_passant_loc]->IsPawn() &&
			(*chess_board)[en_passant_loc]->FirstMove() && chess_board->LastMove() == en_passant_loc;
}

int Pawn::CapturedRank(const std::string& to) {
	auto capture_loc = to;
	if (IsEnPassant(to)) {
		capture_loc = std::string() + to[0] + loc[1];
	}
	std::unique_ptr<Piece>& capture = (*chess_board)[capture_loc];
	if (capture != nullptr) return capture->Priority();
	return -1;
}

bool Pawn::CanMove(const std::string& to) {
	if (chess_board->GetPiecePlayer(to) == player || chess_board->IsRevealingKing(this, to)) return false;
	if (to[0] == loc[0]) {
		if (abs(to[1] - loc[1]) == 1) return chess_board->Empty(to);
		if (abs(to[1] - loc[1]) == 2) return move_count == 0;
	} else 
	if (abs(to[0] - loc[0]) == 1 && abs(to[1] - loc[1]) == 1) {
		return IsEnPassant(to) || !chess_board->Empty(to);
	}
	return false;
}

bool Pawn::CanCapture(const std::string& to) {
	for (const auto& move : *this) {
		if (move == to && abs(to[0] - loc[0]) == 1 && abs(to[1] - loc[1]) == 1) return !chess_board->IsRevealingKing(this, to);
	}
	return false;
}

bool Pawn::CanPromote() {
	if (player == WHITE) return loc[1] == TOP_ROW - 1;
	return loc[1] == BOT_ROW + 1;
}