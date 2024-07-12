#include "move.h"
#include "board.h"

Move::Move(std::string& from, std::string& to) : from{from}, to{to}, first_move{false}, captured{false} {}

bool Move::MakeMoveOn(Board* chess_board) {
	if (!chess_board->ValidMove(from, to)) return 0;
	return chess_board->MovePiece(from, to);
}