#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "subject.h"
#include "board.h"
#include "move.h"
#include <memory>
#include <stack>

class Move;

class ChessBoard : public Subject {
	std::unique_ptr<Board> board; // Board manages the placement of pieces
	bool game_over, captured;

	std::string last_moved;

	public:
		ChessBoard() : board{std::make_unique<Board>()}, game_over{false} {}
		
		/* Game board interface */
		void Reset() { board->reset(); game_over = false; };
		void Clear() { board->clear(); };
		void Print();
		
		void SetPiece(const std::string& loc, char name, char col);
		void RemovePiece(const std::string& loc);
		
		char GetPieceName(const std::string& loc);
		char GetPiecePlayer(const std::string& loc);
		
		bool Empty(const std::string& loc) { return board->empty(loc); }
		bool HasMoved(const std::string& loc);
		
		/* Game status interface */
		bool GameOver() { return game_over; }
		bool Captured() { return captured; }
		
		std::vector<char> WhiteCaptured();
		std::vector<char> BlackCaptured();

		/* Game move interface */
		bool MakeMove(std::unique_ptr<Move>& move);
		bool MovePiece(const std::string& from, const std::string& to);
		bool FirstMove(const std::string& loc) { return board->first_move(loc); }

		void Capture(const std::string& loc) { board->capture(loc); }
		void Recapture(const std::string& loc);

		std::string LastMoved() { return last_moved; }

		/* Helper functions */
		int Distance(const std::string& from, const std::string& to)  {
			return std::abs(from[0] - to[0]) + std::abs(from[1] - to[1]);
		}
};

#endif