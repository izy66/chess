#include "move.h"
#include "board.h"

Move::Move(const std::string& from, const std::string& to) : from{from}, to{to}, first_move{false}, captured{false}, promotion{false} {}

void Move::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) throw _invalid_move_{"This move is not following the rules!"};
	chess_board->MovePiece(from, to);
}