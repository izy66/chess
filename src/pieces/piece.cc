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
		return 0;
	}
	// compare this move with all valid moves
	Piece::Iterator move = begin(loc);
	++move;
	for (; move != end(); ++move) {
		if (*move == to) return 1;
	}
	// no match, not a valid move
	return 0;
}

bool Piece::CanMove(const std::string& to) {
	// can't move away if current piece is protecting the king
	if (chess_board->GetPiecePlayer(to) == player || chess_board->IsRevealingKing(this, to)) {
		return 0;
	}
	// compare this move with all valid moves
	Piece::Iterator move = begin();
	++move;
	for (; move != end(); ++move) {
		if (*move == to) return 1;
	}
	// no match, not a valid move
	return 0;
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