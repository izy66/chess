#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "subject.h"
#include "board.h"
#include <memory>

class ChessBoard : public Subject {
	std::unique_ptr<Board> board; // Board manages the placement of pieces
	bool game_over;

	public:
		ChessBoard() : board{std::make_unique<Board>()}, game_over{false} {}
		void Reset() { board->reset(); game_over = false; };
		void Clear() { board->clear(); };
		void Print();
		void SetPiece(const std::string& loc, char name, char col);
		void RemovePiece(const std::string& loc);
		char GetPieceChar(const std::string& loc);
		char GetPieceColor(const std::string& loc);
		bool MovePiece(const std::string& from, const std::string& to);
		bool GameOver() { return game_over; }
		std::vector<char> WhiteCaptured();
		std::vector<char> BlackCaptured();
};

#endif