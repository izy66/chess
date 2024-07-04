#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include <string>

class Piece : public Board {
	protected:
		// std::string loc;
		char name, col;
	public:
		Piece(char n = ' ', char c = ' ') : name{n}, col{c} {}
		virtual ~Piece();
		virtual char Print(const std::string&) override;
		virtual void Move(const std::string&) = 0;
};

#endif