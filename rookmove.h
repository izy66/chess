#ifndef ROOKMOVE_H
#define ROOKMOVE_H

#include "move.h"

class RookMove : public Move {
	public:
		RookMove(std::string& from, std::string& to) : Move{from, to} {}
		bool MakeMoveOn(ChessBoard*) override;
		void Undo(ChessBoard*) override {}
};

#endif