#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "move.h"

class PawnMove final : public Move {
	char promotion;
	public:
		PawnMove(const std::string& from, const std::string& to, char promo = PAWN) : Move{from, to}, promotion{promo} {}
		void MakeMoveOn(Board*) override;
};

#endif