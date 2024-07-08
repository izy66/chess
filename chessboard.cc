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
	return board->color(loc);
}

bool ChessBoard::MovePiece(const std::string& from, const std::string& to) {

	captured = false;

	if (board->color(from) == board->color(to)) {
		std::cerr << "You can't step over your own pieces!" << std::endl;
		return 0;
	}

	if (tolower(board->get(to)) == 'k') game_over = 1;

	board->move_piece(from, to);
	last_moved = to;

	return 1;
}

bool ChessBoard::HasMoved(const std::string& loc) {
	return board->has_moved(loc);
}

void ChessBoard::Recapture(const std::string& loc) {
	board->recapture(loc);
}

std::vector<char> ChessBoard::WhiteCaptured() {
	return board->captured_color(WHITE);
}

std::vector<char> ChessBoard::BlackCaptured() {
	return board->captured_color(BLACK);
}

bool ChessBoard::MakeMove(std::unique_ptr<Move>& move) {
	return move->MakeMoveOn(this);
}