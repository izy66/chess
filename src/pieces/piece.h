#ifndef PIECE_H
#define PIECE_H

#include "square.h"
#include "iterators/iterator.h"
#include <string>
#include <memory>
#include <iostream>

#define BLACK 'B'
#define WHITE 'W'
#define KING 'K'
#define QUEEN 'Q'
#define BISHOP 'B'
#define KNIGHT 'N'
#define ROOK 'R'
#define PAWN 'P'

class Board;

class Piece {
	protected:
		char name, player; // default capital = WHITE lowercase = BLACK
		bool has_moved, first_move;
	public:
		Piece(char n, char p) : name{n}, player{p}, has_moved{false}, first_move{false} {}
		virtual ~Piece();
		
		char Print() const;
		bool Empty() const { return 0; }

		char Name() const { return name; }
		char Player() const { return player; }

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

		bool HasMoved() const { return has_moved; }
		bool FirstMove() const { return first_move; }

		class Iterator {
			friend class Piece;
			
			std::shared_ptr<PieceIterator> iterator;
			public:

				Iterator(const std::shared_ptr<PieceIterator>& it) : iterator{it} {}
				virtual bool operator!=(const Iterator& other) {
					return *iterator != *other.iterator;
				}
				virtual void operator++() { ++(*iterator); }
				virtual std::string operator*() { return **iterator; }
		};

		virtual Iterator begin(Board* board, const std::string& loc) = 0;
		virtual Iterator end() = 0;
};

#endif