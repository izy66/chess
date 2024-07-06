#include "piece.h"

Piece::~Piece() {}

char Piece::Print(const std::string& loc) const {
	// int x = loc[0] - LEFT_COL;
	// int y = TOP_ROW - loc[1];
	if (col == BLACK) {
		return tolower(name);
	} else {
		return toupper(name);
	}
}