#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "move.h"

class PawnMove final : public Move {
	char promotion;
	public:
		PawnMove(std::string& from, std::string& to, char promo = PAWN) : Move{from, to}, promotion{promo} {}
		bool MakeMoveOn(Board*) override;
		void Undo(Board*) override {}
};

#endif