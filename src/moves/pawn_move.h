#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "abstract_move.h"
#include "pieces/piece.h"

class PawnMove final : public AbstractMove {

	Board *board;
	std::string from, to;

	std::shared_ptr<Piece> captured;
	std::shared_ptr<Piece> promoted;
	char promotion;
	
	public:
	
		PawnMove(const std::string&, const std::string&, char promo = PAWN);
		
		void MakeMoveOn(Board*) override;
		void Undo() noexcept override;
};

#endif