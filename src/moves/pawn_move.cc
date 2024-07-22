#include "pawn_move.h"
#include "pieces/pawn.h"
#include "board.h"

PawnMove::PawnMove(const std::string& from, const std::string& to, char promo) : from{from}, to{to}, captured{nullptr}, promoted{nullptr}, promotion{promo} {}

void PawnMove::MakeMoveOn(Board* chess_board) {
	board = chess_board;

	if (!(*board)[from]->CanMove(to) && !(*board)[from]->IsEnPassant(to)) throw _invalid_move_{"Can't move from " + from + " to " + to};
	
	if (from[0] != to[0] && from[1] != to[1]) {
		captured = board->Retrieve(to);
	}
	
	if ((*board)[from]->IsEnPassant(to)) {
		auto enpas_loc = std::string() + to[0] + from[1];
		captured = board->Retrieve(enpas_loc);
	}
	
	if (captured != nullptr) board->Capture(captured->Name(), captured->Player());

	// handle promotion
	if ((*board)[from]->CanPromote()) {

		promoted = board->Retrieve(from);
		board->SetPiece(from, promotion, promoted->Player());
	}
	
	(*board)[from]->TakeMove(to); // then move pawn / promoted piece 
}

void PawnMove::Undo() noexcept {
	(*board)[to]->UndoMove(from);
	board->Place(std::move(promoted));
	
	if (captured != nullptr) {
		board->Release(captured->Player());
		board->Place(std::move(captured));
	}
}