#ifndef KING_MOVE_H
#define KING_MOVE_H

#include "move.h"
#include <string>

class KingMove : public Move {
	public:
		KingMove(std::string& from, std::string& to);
		bool MakeMoveOn(ChessBoard*) override;
		void Undo(ChessBoard*) override;
};

#endif