#include "pawn_move.h"
#include "pieces/pawn.h"

bool PawnMove::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) return 0;
	captured = chess_board->IsCaptureMove(from, to);
	if (chess_board->IsEnPassant(from, to)) {
		std::string enpas_loc = std::string() + to[0] + from[1];
		captured = 1;
		chess_board->Capture(enpas_loc);
	}
	if (chess_board->CanPromote(from)) {
		chess_board->SetPiece(from, promotion, chess_board->GetPiecePlayer(from));
	}
	chess_board->MovePiece(from, to);
	return 1;
}