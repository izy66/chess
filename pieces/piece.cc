#include "piece.h"

Piece::~Piece() {}

char Piece::Print() const {
	if (col == BLACK) {
		return tolower(name);
	} else {
		return toupper(name);
	}
}