#include "pawn.h"
#include "board.h"

bool Pawn::IsEnPassant(const std::string& to) const {
	if (loc[0] == to[0] || abs(loc[1] - to[1]) > 1) return 0;
	std::string en_passant_loc = std::string() + to[0] + loc[1];
	return (*chess_board)[en_passant_loc] != nullptr && (*chess_board)[en_passant_loc]->IsPawn() &&
			(*chess_board)[en_passant_loc]->FirstMove() && chess_board->LastMove() == en_passant_loc;
}