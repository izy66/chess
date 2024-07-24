#include "piece.h"
#include "chessboard.h"
#include "moves/move.h"

Piece::~Piece() {}

bool Piece::CanCapture(const std::string& to) {
	// can't move away if current piece is protecting the king
	if (board->IsRevealingKing(this, to)) {
		return false;
	}
	// compare this move with all valid moves
	for (const auto move : *this) {
		if (move == to) return true;
	}
	// no match, not a valid move
	return false;
}

bool Piece::CanMove(const std::string& to) {
	// piece can move if it's following the rules and not stepping over
	return board->GetPiecePlayer(to) != player && CanCapture(to);
}

bool Piece::CanPromote(const std::string& to) {
	return false;
}

int Piece::CapturedRank(const std::string& loc) {
	std::unique_ptr<Piece>& capture = (*board)[loc];
	if (capture != nullptr) return capture->Priority();
	return -1;
}

bool Piece::CanGetCaptured(const std::string& loc) {
	return board->CanBeCaptured(loc, player);
}

void Piece::TakeMove(const std::string& to) {
	board->MovePiece(loc, to);
	loc = to;
	++move_count;
}

void Piece::UndoMove(const std::string& from) {
	board->UndoMove(from, loc);
	loc = from;
	--move_count;
}