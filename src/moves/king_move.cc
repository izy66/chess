#include "king_move.h"
#include "chessboard.h"

KingMove::KingMove(const std::string& from, const std::string& to) : Move{from, to} {}

void KingMove::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) throw _invalid_move_{"This move is not following the rules!"};
	// valid move
	if (chess_board->IsCastling(from, to)) { // if castling
		std::string rook_dest = from;
		rook_dest[0] += (to[0] - from[0]) / 2;
		std::string rook_loc = rook_dest;
		while (chess_board->InBound(rook_loc)) {
			if (toupper(chess_board->GetPieceName(rook_loc)) == ROOK) break;
			rook_loc[0] += (to[0] - from[0]) / 2;
		}
		chess_board->MovePiece(rook_loc, rook_dest);
	}
	captured = chess_board->IsCaptureMove(from, to);
	chess_board->MovePiece(from, to);
}