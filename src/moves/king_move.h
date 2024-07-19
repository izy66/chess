#ifndef KING_MOVE_H
#define KING_MOVE_H

#include "move.h"

class KingMove final : public Move {
	public:
		KingMove(const std::string& from, const std::string& to);
		void MakeMoveOn(Board*) override;
};

#endif