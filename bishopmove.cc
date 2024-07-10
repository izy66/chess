#include "bishopmove.h"

bool BishopMove::MakeMoveOn(Board* chess_board) {
	if (abs(from[0] - to[0]) == abs(from[1] - to[1])) {
		int col_dir = (to[1] - from[1]) / (to[0] - from[0]);
		for (char col = std::min(from[0], to[0]) + 1, row = std::min(from[1], to[1]) + 1; 
							col <= std::max(from[0], to[0]) - 1; col += col_dir, ++row) {
			std::string path = std::string() + col + row;
			if (!chess_board->Empty(path)) {
				return 0; // pieces blocking bishop's move
			}
		}
		return chess_board->MovePiece(from, to);
	} else {
		return 0;
	}
}