#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "iterators/queen_iterator.h"

class Queen : public Piece {
	public:
		Queen(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, QUEEN, player} {}

		Iterator begin() override {
			return Iterator{std::make_shared<QueenIterator>(chess_board, loc)};
		}
		Iterator begin(const std::string& loc) override {
			return Iterator{std::make_shared<QueenIterator>(chess_board, loc)};
		}
		Iterator end() override {
			return Iterator{std::make_shared<QueenIterator>(chess_board, "  ")};
		}
};

#endif