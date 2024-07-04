#include <iostream>

#include "chessboard.h"
// #include "board.h"
// #include "piece.h"

void ChessBoard::Reset() {
	board->clear();
	board->set("a1", 'R', WHITE);
	board->set("b1", 'N', WHITE);
	board->set("c1", 'B', WHITE);
	board->set("d1", 'Q', WHITE);
	board->set("e1", 'K', WHITE);
	board->set("f1", 'B', WHITE);
	board->set("g1", 'N', WHITE);
	board->set("h1", 'R', WHITE);
	for (char c = 'a'; c <= 'h'; ++c) {
		board->set(std::string() + c + '2', 'P', WHITE);
	}
	board->set("a8", 'r', BLACK);
	board->set("b8", 'n', BLACK);
	board->set("c8", 'b', BLACK);
	board->set("d8", 'q', BLACK);
	board->set("e8", 'k', BLACK);
	board->set("f8", 'b', BLACK);
	board->set("g8", 'n', BLACK);
	board->set("h8", 'r', BLACK);
	for (char c = 'a'; c <= 'h'; ++c) {
		board->set(std::string() + c + '7', 'p', BLACK);
	}
}

void ChessBoard::Print() {
	for (char r = TOP_ROW; r >= BOT_ROW; --r) {
		std::cout << r << ' ';
		for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
			std::cout << board->get(c, r) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;
}

void ChessBoard::SetPiece(const std::string& loc, char name, char col) {
	board->set(loc, name, col);
}

void ChessBoard::RemovePiece(const std::string& loc) {
	board->remove(loc);
}
