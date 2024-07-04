#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <memory>

#include "set.h"

class ChessBoard {
	std::unique_ptr<Set> board;

	public:
		ChessBoard() : board{std::make_unique<Set>()} {}
		void Reset();
		void Print();
		void SetPiece(const std::string& loc, char name, char col);
		void RemovePiece(const std::string& loc);
};

#endif