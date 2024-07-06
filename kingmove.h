#ifndef KING_MOVE_H
#define KING_MOVE_H

#include "command.h"
#include "pieces/piece.h"
#include "chessboard.h"

class KingMove : public Command {
	ChessBoard *chess_board;
	Piece *captured;
	std::string from, to;
	public:
		KingMove(const std::string& from, const std::string& to, ChessBoard* board);
		bool Execute() override;
		void Undo() override;
};

#endif