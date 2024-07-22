#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "iterators/knight_iterator.h"

class Knight : public Piece {
	public:
		Knight(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, KNIGHT, player} {}

		Knight(const Piece& other) : Piece{other} {
			name = KNIGHT;
		}

		int Priority() const override { return Piece::KNIGHT_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<KnightIterator>(chess_board, loc)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<KnightIterator>(chess_board, "  ")};
		}
};

#endif