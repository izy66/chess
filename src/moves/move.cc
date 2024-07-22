#include "move.h"
#include "board.h"

Move::Move(const std::string& from, const std::string& to) : from{from}, to{to}, capture_count{0}, captured{nullptr} {}

void Move::MakeMoveOn(Board* chess_board) {
	if (!(*chess_board)[from]->CanMove(to)) throw _invalid_move_{"Can't move from " + from + " to " + to};
	board = chess_board;

	captured = board->Retrieve(to);

	if (captured != nullptr) board->Capture(captured->Name(), captured->Player());

	(*board)[from]->TakeMove(to);
}

void Move::Undo() noexcept {
	(*board)[to]->UndoMove(from);
	
	if (captured != nullptr) {
		board->Release(captured->Player());
		board->Place(std::move(captured));
	}
}