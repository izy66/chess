#include <iostream>

#include "chessboard.h"

void ChessBoard::Print() {
	NotifyObservers();
}

void ChessBoard::SetPiece(const std::string& loc, char name, char col) {
	if (board->set(loc, name, col)) {
		Print();
	}
}

void ChessBoard::RemovePiece(const std::string& loc) {
	if (board->remove(loc)) {
		Print();
	}
}

char ChessBoard::GetPieceChar(const std::string& loc) {
	return board->get(loc);
}

char ChessBoard::GetPieceColor(const std::string& loc) {
	return board->get_color(loc);
}

bool ChessBoard::MovePiece(const std::string& from, const std::string& to) {

	if (tolower(board->get(to)) == 'k') game_over = 1;

	if (!board->empty(to)) board->capture(to);
	board->set(to, board->get(from), board->get_color(from));
	board->remove(from);

	return 1;
}

std::vector<char> ChessBoard::WhiteCaptured() {
	return board->captured_color(WHITE);
}

std::vector<char> ChessBoard::BlackCaptured() {
	return board->captured_color(BLACK);
}