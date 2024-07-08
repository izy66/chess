#ifndef BISHOPMOVE_H
#define BISHOPMOVE_H

#include "move.h"

class BishopMove : public Move {
	public:
		BishopMove(std::string& from, std::string& to) : Move{from, to} {}
		bool MakeMoveOn(ChessBoard*) override;
		void Undo(ChessBoard*) override {}
};

#endif