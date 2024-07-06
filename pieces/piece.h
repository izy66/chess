#ifndef PIECE_H
#define PIECE_H

#include "square.h"
#include <string>

#define BLACK 'B'
#define WHITE 'W'

class Piece : public Square {
	protected:
		// std::string loc;
		char name, col; // default capital = WHITE lowercase = BLACK
	public:
		Piece(char n = ' ', char c = ' ') : name{n}, col{c} {}
		virtual ~Piece();
		
		char Print(const std::string&) const override;
		bool Empty() const override { return 0; }

		char Name() const { return name; }
		char Color() const { return col; }
		
		virtual void Move(const std::string&) = 0;
};

#endif