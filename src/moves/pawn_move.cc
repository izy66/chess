#include "pawn_move.h"
#include "pieces/pawn.h"
#include "board.h"

PawnMove::PawnMove(const std::string& from, const std::string& to, char promo) : from{from}, to{to}, captured{nullptr}, promoted{nullptr}, promotion{promo} {}

void PawnMove::MakeMoveOn(Board* chess_board) {
	if (!(*chess_board)[from]->CanMove(to) && !(*chess_board)[from]->IsEnPassant(to)) throw _invalid_move_{"Can't move from " + from + " to " + to};
	board = chess_board;
	if (from[0] != to[0] && from[1] != to[1]) {
		captured = board->Capture(to);
	}
	if ((*board)[from]->IsEnPassant(to)) {
		auto enpas_loc = std::string() + to[0] + from[1];
		captured = board->Capture(enpas_loc);
	}
	// handle promotion
	if (board->CanPromote(from)) {
		promoted = std::move((*board)[from]);
		switch (toupper(promotion)) {
				case QUEEN:
					(*board)[from] = std::make_shared<Queen>(*promoted);
					break;
				case BISHOP:
					(*board)[from] = std::make_shared<Bishop>(*promoted);
					break;
				case KNIGHT:
					(*board)[from] = std::make_shared<Knight>(*promoted);
					break;
				case ROOK:
					(*board)[from] = std::make_shared<Rook>(*promoted);
					break;
				default:
					(*board)[from] = std::make_shared<Queen>(*promoted);
					break;
		}
	}
	(*board)[from]->TakeMove(to); // then move pawn / promoted piece 
}

void PawnMove::Undo() {
	(*board)[to]->UndoMove(from);
	board->Release(std::move(captured));
	board->Release(std::move(promoted));
}