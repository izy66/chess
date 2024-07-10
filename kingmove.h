#ifndef KING_MOVE_H
#define KING_MOVE_H

#include "move.h"

class KingMove : public Move {
	public:
		KingMove(std::string& from, std::string& to);
		bool MakeMoveOn(Board*) override;
		void Undo(Board*) override;
};

#endif