#include "king_move.h"
#include "chessboard.h"

KingMove::KingMove(const std::string& from, const std::string& to) : from{from}, to{to} {}

void KingMove::MakeMoveOn(Board* chess_board) {
	if (!(*chess_board)[from]->CanMove(to) && !(*chess_board)[from]->IsCastling(to)) throw _invalid_move_{"Can't move from " + from + " to " + to};
	board = chess_board;
	// valid move
	if ((*board)[from]->IsCastling(to)) { // if castling
		rook_dest = from;
		rook_dest[0] += (to[0] - from[0]) / 2;
		rook_loc = rook_dest;

		while (board->InBound(rook_loc)) {
			if (toupper(board->GetPieceName(rook_loc)) == ROOK) break;
			rook_loc[0] += (to[0] - from[0]) / 2;
		}
		// board->MovePiece(rook_loc, rook_dest);
		rook = (*board)[rook_loc];
		rook->TakeMove(rook_dest);
	}
	captured = board->Capture(to);
	(*board)[from]->TakeMove(to);
	board->KingIsHere(to);
}

void KingMove::Undo() noexcept {
	if (rook != nullptr) rook->UndoMove(rook_loc);
	(*board)[to]->UndoMove(from);
	board->KingIsHere(from);
	board->Release(captured);
}