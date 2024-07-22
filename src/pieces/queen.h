#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "iterators/queen_iterator.h"

class Queen : public Piece {
	public:
		Queen(Board* chess_board, const std::string& loc, char player) : Piece{chess_board, loc, QUEEN, player} {}

		Queen(const Piece& other) : Piece{other} {
			name = QUEEN;
		}

		int Priority() const override { return Piece::QUEEN_RANK; }

		Iterator begin() override {
			auto iter = Iterator{std::make_shared<QueenIterator>(chess_board, loc)};
			++iter;
			return iter;
		}

		Iterator end() override {
			return Iterator{std::make_shared<QueenIterator>(chess_board, "  ")};
		}
};

#endif