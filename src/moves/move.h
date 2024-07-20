#ifndef MOVE_H
#define MOVE_H

#include "abstract_move.h"

class Board;
class Piece;

class Move final : public AbstractMove {

	Board *board;
	std::string from, to;

	size_t capture_count;
	std::shared_ptr<Piece> captured;

	public:

		Move(const std::string& from, const std::string& to);

		Move(Move& other) {
			from = other.from;
			to = other.to;
			capture_count = other.capture_count;
			// piece = other.piece;
			// promoted = other.promoted;
			captured = other.captured;
			// first_move = other.first_move;
			// captured = other.captured;
		}

		virtual void MakeMoveOn(Board*) override; // return 1 if execution is successful
		virtual void Undo() noexcept override; // any valid execution can be undone
		// bool IsPromotion() { return promotion; }
};

#endif