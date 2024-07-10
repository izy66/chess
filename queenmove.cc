#include "queenmove.h"

bool QueenMove::MakeMoveOn(Board* chess_board) {
	if (from[0] == to[0]) {
		for (char row = std::min(from[1], to[1]) + 1; row <= std::max(from[1], to[1]) - 1; ++row) {
			std::string path = std::string() + from[0] + row;
			if (!chess_board->Empty(path)) {
				return 0; // pieces blocking queen's move
			}
		}
		return chess_board->MovePiece(from, to);
	} else 
	if (from[1] == to[1]) {
		for (char col = std::min(from[0], to[0]) + 1; ; ++col) {
			std::string path = std::string() + col + from[1];
			if (!chess_board->Empty(path)) {
				return 0; // pieces blocking queen's move
			}
		}
		return chess_board->MovePiece(from, to);
	} else 
	if (abs(from[0] - to[0]) == abs(from[1] - to[1])) {
		int col_dir = (to[1] - from[1]) / (to[0] - from[0]);
		for (char col = std::min(from[0], to[0]) + 1, row = std::min(from[1], to[1]) + 1; 
							col <= std::max(from[0], to[0]) - 1; col += col_dir, ++row) {
			std::string path = std::string() + col + row;
			if (!chess_board->Empty(path)) {
				return 0; // pieces blocking queen's move
			}
		}
		return chess_board->MovePiece(from, to);
	} else {
		return 0;
	}
}