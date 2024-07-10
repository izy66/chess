#include "kingmove.h"
#include "chessboard.h"

KingMove::KingMove(std::string& from, std::string& to) : Move{from, to} {}

bool KingMove::MakeMoveOn(Board* chess_board) {
	if (chess_board->Distance(from, to) == 2 && (from[0] == to[0] || from[1] == to[1])) return 0;
	if (chess_board->Distance(from, to) > 2) return 0;
	// valid move 
	chess_board->MovePiece(from, to);
	captured = chess_board->Captured();
	return 1;
}

void KingMove::Undo(Board* chess_board) {
}