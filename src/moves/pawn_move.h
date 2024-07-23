#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "abstract_move.h"
#include "pieces/piece.h"

class PawnMove final : public AbstractMove {

	Board *my_board;
	std::string from, to;

	std::unique_ptr<Piece> captured;
	std::unique_ptr<Piece> promoted;
	char promotion;
	
	public:
	
		PawnMove(const std::string&, const std::string&, char promo = PAWN);
		
		void MakeMoveOn(Board*) override;
		void Undo() noexcept override;
};

#endif