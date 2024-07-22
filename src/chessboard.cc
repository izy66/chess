#include "chessboard.h"
#include "player/player.h"
#include <iostream>

char ChessBoard::PrintPieceName(const std::string& loc) {
	// if (players[player] != nullptr && !players[player]->CanSee(loc) && GetPiecePlayer(loc) != player) return FOG;
	// if (players[player] == nullptr || !players[player]->CanSee(loc)) return FOG;
	if (Empty(loc)) return ' ';
	return pieces[loc]->Name();
}