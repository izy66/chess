#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "iterators/knight_iterator.h"

class Knight : public Piece {
	public:
		Knight(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, KNIGHT, player} {}

		Iterator begin() override {
			return Iterator{std::make_shared<KnightIterator>(chess_board, loc)};
		}
		Iterator begin(const std::string& loc) override {
			return Iterator{std::make_shared<KnightIterator>(chess_board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<KnightIterator>(chess_board, "  ")};
		}
};

#endif