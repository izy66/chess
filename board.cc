#include "board.h"
#include "pieces/blank.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"

bool Board::set(const std::string& loc, char name, char col) {
	if (name == get(loc)) return 0; // don't need to set again
	switch(tolower(name)) {
		case 'k':
			pieces[loc] = std::make_unique<King>(col);
			break;
		case 'q':
			pieces[loc] = std::make_unique<Queen>(col);
			break;
		case 'b':
			pieces[loc] = std::make_unique<Bishop>(col);
			break;
		case 'n':
			pieces[loc] = std::make_unique<Knight>(col);
			break;
		case 'p':
			pieces[loc] = std::make_unique<Pawn>(col);
			break;
		case 'r':
			pieces[loc] = std::make_unique<Rook>(col);
			break;
	}
	return 1;
}

char Board::get(const std::string& loc) { 
	if (empty(loc)) return blank.Print(loc);
	return pieces[loc]->Print(); 
}

char Board::color(const std::string& loc) {
	if (empty(loc)) return blank.Print(loc);
	return pieces[loc]->Color();
}

bool Board::remove(const std::string& loc) {
	if (pieces[loc] == BLANK) return 0; // nothing to remove
	pieces[loc] = BLANK;
	return 1;
}

void Board::clear() {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			remove(std::string() + c + r);
		}
	}
}

void Board::reset() {
	clear();
	set("a1", 'R', WHITE);
	set("b1", 'N', WHITE);
	set("c1", 'B', WHITE);
	set("d1", 'Q', WHITE);
	set("e1", 'K', WHITE);
	set("f1", 'B', WHITE);
	set("g1", 'N', WHITE);
	set("h1", 'R', WHITE);
	for (char c = 'a'; c <= 'h'; ++c) {
		set(std::string() + c + '2', 'P', WHITE);
	}
	set("a8", 'r', BLACK);
	set("b8", 'n', BLACK);
	set("c8", 'b', BLACK);
	set("d8", 'q', BLACK);
	set("e8", 'k', BLACK);
	set("f8", 'b', BLACK);
	set("g8", 'n', BLACK);
	set("h8", 'r', BLACK);
	for (char c = 'a'; c <= 'h'; ++c) {
		set(std::string() + c + '7', 'p', BLACK);
	}
	captured_white.clear();
	captured_black.clear();
}

void Board::capture(const std::string& loc) {
	if (pieces[loc] != BLANK) {
		if (pieces[loc]->Color() == BLACK) {
			captured_white.emplace_back(pieces[loc]->Name());
		} else {
			captured_black.emplace_back(pieces[loc]->Name());
		}
		captured_pieces.push(std::move(pieces[loc]));
		pieces[loc] = BLANK;
	}
}

void Board::recapture(const std::string& loc) {
	pieces[loc] = std::move(captured_pieces.top());
	if (pieces[loc]->Color() == BLACK) captured_white.pop_back();
	else captured_black.pop_back();
	captured_pieces.pop();
}

std::vector<char> Board::captured_color(char color) {
	if (color == WHITE) {
		return captured_white;
	} else {
		return captured_black;
	}
}

void Board::move_piece(const std::string& from, const std::string& to) {
	if (pieces[to] != BLANK) capture(to);
	pieces[from]->JustMoved();
	pieces[to] = std::move(pieces[from]);
}