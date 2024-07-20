#include "move.h"
#include "board.h"

Move::Move(const std::string& from, const std::string& to) : from{from}, to{to}, capture_count{0}, captured{nullptr} {}

void Move::MakeMoveOn(Board* chess_board) {
	if (!(*chess_board)[from]->CanCover(to)) throw _invalid_move_{"Can't move from " + from + " to " + to};
	board = chess_board;
	captured = board->Capture(to);
	(*board)[from]->TakeMove(to);
}

void Move::Undo() {
	(*board)[to]->UndoMove(from);
	board->Release(std::move(captured));
}