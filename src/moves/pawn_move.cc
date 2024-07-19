#include "pawn_move.h"
#include "pieces/pawn.h"

void PawnMove::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) throw _invalid_move_{"This move is not following the rules!"};
	captured = chess_board->IsCaptureMove(from, to);
	if (chess_board->IsEnPassant(from, to)) {
		std::string enpas_loc = std::string() + to[0] + from[1];
		captured = 1;
		chess_board->Capture(enpas_loc);
	}
	// handle promotion
	if (chess_board->CanPromote(from)) {
		chess_board->Promote(from, promotion); // first remove the pawn from chess board
		promotion = true;
	}
	chess_board->MovePiece(from, to); // move pawn/promoted piece 
}