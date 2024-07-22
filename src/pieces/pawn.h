#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "iterators/pawn_iterator.h"

class Pawn : public Piece {
	public:
		Pawn(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, PAWN, player} {}

		bool IsPawn() const override { return true; }
		bool IsEnPassant(const std::string&) const override; 

		bool CanCover(const std::string&) override;
		bool CanMove(const std::string&) override;

		int Priority() const override { return Piece::PAWN_RANK; }

		int CapturedRank(const std::string&) override;

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<PawnIterator>(chess_board, loc)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<PawnIterator>(chess_board, "xx")};
		}
};

#endif