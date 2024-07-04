#include "set.h"
#include "pieces/blank.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"

void Set::set(const std::string& loc, char name, char col) {
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
}

void Set::remove(const std::string& loc) {
	pieces[loc] = std::make_unique<Blank>();
}

void Set::clear() {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			remove(std::string() + c + r);
		}
	}
}