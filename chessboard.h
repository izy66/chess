#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "board.h"
#include <memory>
#include <stack>

class Move;

class ChessBoard : public Board {
	public:
		char GetPieceName(const std::string& loc) override; // overwritten in Fog of War
};

#endif