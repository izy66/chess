#include "king_move.h"
#include "chessboard.h"

KingMove::KingMove(std::string& from, std::string& to) : Move{from, to} {}

bool KingMove::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) {
		// check castling condition
		if (chess_board->Check()) return 0;
		int castle_dest = to[0] - from[0];
		if (abs(castle_dest) != 2) return 0;
		std::string rook_loc = to;
		while (chess_board->in_bound(rook_loc)) {
			if (tolower(chess_board->GetPieceName(rook_loc)) == tolower(ROOK)) {
				if (!chess_board->HasItMoved(from) && !chess_board->HasItMoved(rook_loc)) {
					std::string rook_dest = from;
					rook_dest[0] += castle_dest / 2;
					return chess_board->MovePiece(from, to) && chess_board->MovePiece(rook_loc, rook_dest);
				}
				return 0;
			}
			rook_loc[0] += castle_dest / 2;
		}
		return 0;
	}
	// valid move
	chess_board->MovePiece(from, to);
	captured = chess_board->Captured();
	return 1;
}

void KingMove::Undo(Board* chess_board) {}