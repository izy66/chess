#ifndef QUEENMOVE_H
#define QUEENMOVE_H

#include "move.h"

class QueenMove : public Move {
	public:
		QueenMove(std::string& from, std::string& to) : Move{from, to} {}
		bool MakeMoveOn(ChessBoard*) override;
		void Undo(ChessBoard*) override {}
};

#endif