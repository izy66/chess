#include "pawn_move.h"
#include "pieces/pawn.h"

bool PawnMove::MakeMoveOn(Board* chess_board) {
	if (chess_board->GetPiecePlayer(from) == WHITE && to[1] - from[1] <= 0) {
		return 0;
	}
	if (chess_board->GetPiecePlayer(from) == BLACK && to[1] - from[1] >= 0) {
		return 0;
	}
	
	int distance = chess_board->Distance(from, to);
	
	if (distance > 2) return 0;
	if (distance == 2) { // must be a capture move, or is it?
		if (from[0] == to[0]) {
			if (chess_board->HasItMoved(from)) {
				// can't move two squares if not first move
				return 0;
			} else {
				first_move = true; // pawn made an initiation move
				return chess_board->MovePiece(from, to);
			}
		} else { // must be a diagonal move then 
			if (!chess_board->Empty(to)) { // capture move, ok
				if (chess_board->MovePiece(from, to)) { // captured
					captured = true;
					return 1;
				} else { // can't make the move, don't know why
					return 0;
				}
			} else { // could it be en passant? 
				std::string en_passant_loc = std::string() + to[0] + from[1];
				if (tolower(chess_board->GetPieceName(en_passant_loc)) == 'p'
				&& chess_board->FirstMove(en_passant_loc) 
				&& chess_board->LastMovedLoc() == en_passant_loc) {
					if (chess_board->MovePiece(from, to)) {
						chess_board->Capture(en_passant_loc);
						return 1;
					}
					return 0;
				} else { // not en passant
					return 0;
				}
			} 
		} 	
	} else {
		return chess_board->MovePiece(from, to);
	}
}