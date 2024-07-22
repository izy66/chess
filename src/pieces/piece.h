#ifndef PIECE_H
#define PIECE_H

// #include "square.h"
#include "iterators/iterator.h"
#include <string>
#include <memory>
#include <iostream>
#include <stack>

#define BLACK 'B'
#define WHITE 'W'
#define KING 'K'
#define QUEEN 'Q'
#define BISHOP 'B'
#define KNIGHT 'N'
#define ROOK 'R'
#define PAWN 'P'

class Board;
class Move;

class Piece {
	
	protected:
		
		Board* chess_board;
		std::string loc;
		char name, player; // default capital = WHITE lowercase = BLACK
		int move_count;
	
	public:
	
		Piece(Board* chess_board, const std::string& loc, char n, char p) : chess_board{chess_board}, loc{loc}, name{n}, player{p}, move_count{0} {}

		Piece(const Piece& other) : chess_board{other.chess_board}, loc{other.loc}, name{other.name}, player{other.player}, move_count{other.move_count} {}
		
		virtual ~Piece();
		
		char Print() const;
		bool Empty() const { return false; }

		static const int HIGHEST_RANK = 100;
		static const int PAWN_RANK = 2;
		static const int KNIGHT_RANK = 9;
		static const int BISHOP_RANK = 10;
		static const int ROOK_RANK = 20;
		static const int QUEEN_RANK = 50;
		static const int KING_RANK = 100;

		virtual int Priority() const { return false; }

		char Name() const { return name; }
		char Player() const { return player; }
		std::string Location() const { return loc; }

		bool HasMoved() const { return move_count != 0; }
		bool FirstMove() const { return move_count == 1; }

		void TakeMove(const std::string&);
		void UndoMove(const std::string&);
		// void MakeMove(const std::string&);

		// if an opponent piece is on this square, can I capture?
		virtual bool CanCover(const std::string&);
		// can I move to this square?
		virtual bool CanMove(const std::string&);
		virtual bool CanPromote();
		
		bool CanGetCaptured(const std::string&);
		virtual int CapturedRank(const std::string&);
		
		virtual bool IsKing() const { return false; }
		virtual bool IsPawn() const { return false; }
		virtual bool IsRook() const { return false; }

		virtual bool IsEnPassant(const std::string& to) const { return false; };
		virtual bool IsCastling(const std::string& to) const { return false; };

		/* iterate through all squares that can either move to or attack */
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

		// virtual Iterator begin(const std::string& loc) = 0;
		virtual Iterator begin() = 0;
		virtual Iterator end() = 0;
};

#endif