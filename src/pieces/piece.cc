#include "piece.h"
#include "chessboard.h"

Piece::~Piece() {}

char Piece::Print() const {
	if (player == BLACK) {
		return tolower(name);
	} else {
		return toupper(name);
	}
}

bool Piece::ValidMove(const std::string& to) {
	// can't move away if current piece is protecting the king
	if (chess_board->IsProtectingKing(loc)) {
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

void Piece::TakeMove(const std::string& to) {
	loc = to;
	++move_count;
}