#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "iterators/pawn_iterator.h"

class Pawn : public Piece {
	public:
		Pawn(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, PAWN, player} {}

		bool IsPawn() const override { return true; }
		bool IsEnPassant(const std::string&) const override; 

		Iterator begin() override {
			return Iterator{std::make_shared<PawnIterator>(chess_board, loc)};
		}
		Iterator begin(const std::string& sloc) override {
			return Iterator{std::make_shared<PawnIterator>(chess_board, sloc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<PawnIterator>(chess_board, "xx")};
		}
};

#endif