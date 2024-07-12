#include "king_move.h"
#include "chessboard.h"

KingMove::KingMove(std::string& from, std::string& to) : Move{from, to} {}

bool KingMove::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) return 0;
	// valid move
	if (chess_board->IsCastling(from, to)) { // if castling
		std::string rook_dest = from;
		rook_dest[0] += (to[0] - from[0]) / 2;
		std::string rook_loc = rook_dest;
		while (chess_board->in_bound(rook_loc)) {
			if (toupper(chess_board->GetPieceName(rook_loc)) == ROOK) break;
			rook_loc[0] += (to[0] - from[0]) / 2;
		}
		return chess_board->MovePiece(from, to) && chess_board->MovePiece(rook_loc, rook_dest);
	}
	captured = chess_board->IsCaptureMove(from, to);
	return chess_board->MovePiece(from, to);
}

void KingMove::Undo(Board* chess_board) {}