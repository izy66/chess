#include "king.h"
#include "board.h"

bool King::ValidMove(const std::string& to) {
	if (chess_board->CanBeCaptured(to)) return 0;
	Piece::Iterator move = begin(loc);
	++move;
	for (; move != end(); ++move) {
		if (*move == to) return 1;
	}
	return 0;
}