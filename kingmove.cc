#include "kingmove.h"

KingMove::KingMove(const std::string& from, const std::string& to, ChessBoard* board) :
		from{from}, to{to}, chess_board{board} {}

bool KingMove::Execute() {
	if (Distance(from, to) > 2) return 0;
	if (Distance(from, to) == 2 && (from[0] == to[0] || from[1] == to[1])) return 0;
	
	// valid move 

}