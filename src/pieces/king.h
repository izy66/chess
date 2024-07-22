#ifndef KING_H
#define KING_H

#include "piece.h"
#include "iterators/king_iterator.h"

class King : public Piece {
	public:
		King(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, KING, player} {}

		bool CanMove(const std::string&) override;
		bool CanCover(const std::string&) override;
		bool IsKing() const override { return true; }
		bool IsCastling(const std::string&) const override;
		
		int Priority() const override { return Piece::KING_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<KingIterator>(chess_board, loc)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<KingIterator>(chess_board, "  ")};
		}
};

#endif