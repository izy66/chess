#include "chessboard.h"
#include <iostream>

char ChessBoard::GetPieceName(const std::string& loc) {
	// if (visibility_counter[player][loc] == 0 && (Empty(loc) || pieces[loc]->Player() != player)) return FOG;
	if (Empty(loc)) return blank.Print(loc);
	return pieces[loc]->Name();
}