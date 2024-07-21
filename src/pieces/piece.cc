#include "piece.h"
#include "chessboard.h"
#include "moves/move.h"

Piece::~Piece() {}

char Piece::Print() const {
	if (player == BLACK) {
		return tolower(name);
	} else {
		return toupper(name);
	}
}

bool Piece::CanCover(const std::string& to) {
	// can't move away if current piece is protecting the king
	if (chess_board->IsRevealingKing(this, to)) {
		return false;
	}
	// compare this move with all valid moves
	for (const auto& move : *this) {
		if (move == to) return true;
	}
	// no match, not a valid move
	return false;
}

bool Piece::CanMove(const std::string& to) {
	// can't move away if current piece is protecting the king
	return chess_board->GetPiecePlayer(to) != player && !chess_board->IsRevealingKing(this, to);
}

int Piece::CapturedRank(const std::string& loc) {
	auto capture = (*chess_board)[loc];
	if (capture != nullptr) return capture->Priority();
	return -1;
}

bool Piece::CanGetCaptured(const std::string& loc) {
	return chess_board->CanBeCaptured(loc, player);
}

void Piece::TakeMove(const std::string& to) {
	chess_board->MovePiece(loc, to);
	loc = to;
	++move_count;
}

void Piece::UndoMove(const std::string& from) {
	chess_board->UndoMove(from, loc);
	loc = from;
	--move_count;
}

void Piece::MakeMove(const std::string& loc) {
	
}

void Piece::UndoMove() {
	chess_board->Undo();
}