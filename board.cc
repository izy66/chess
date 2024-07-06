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

bool Board::remove(const std::string& loc) {
	if (pieces[loc] != nullptr && pieces[loc]->Empty()) return 0; // nothing to remove
	pieces[loc] = std::make_unique<Blank>();
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
}

std::vector<char> Board::captured_color(char color) {
	std::vector<char> captured_list;
	for (const auto& captured: captured_pieces) {
		if ((isupper(captured) && color == WHITE)
		|| (islower(captured) && color == BLACK)) {
			captured_list.push_back(captured);
		}
	}
	return captured_list;
}
