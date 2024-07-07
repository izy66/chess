#ifndef PIECE_H
#define PIECE_H

#include "square.h"
#include <string>

#define BLACK 'B'
#define WHITE 'W'

class Piece {
	protected:
		// std::string loc;
		char name, col; // default capital = WHITE lowercase = BLACK
		bool has_moved, first_move;
	public:
		Piece(char n, char c) : name{n}, col{c}, has_moved{false}, first_move{false} {}
		virtual ~Piece();
		
		char Print() const;
		bool Empty() const { return 0; }

		char Name() const { return name; }
		char Color() const { return col; }

		void JustMoved() { 
			if (!has_moved) first_move = true; 
			else first_move = false;
			has_moved = true; 
		}

		void UndoMoved() { 
			if (has_moved && first_move) {
				has_moved = first_move = false;
			}
		}

		bool HasMoved() { return has_moved; }
		bool FirstMove() { return first_move; }
		
		virtual void Move(const std::string&) = 0;
};

#endif