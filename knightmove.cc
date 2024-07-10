#include "knightmove.h"

bool KnightMove::MakeMoveOn(Board* chess_board) {
	int row_dist = abs(from[0] - to[0]);
	int col_dist = abs(from[1] - to[1]);
	if ((row_dist == 1 && col_dist == 2) || (row_dist == 2 && col_dist == 1)) {
		return chess_board->MovePiece(from, to);
	} else {
		return 0;
	}
}