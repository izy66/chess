#include "piece.h"

Piece::~Piece() {}

char Piece::Print() const {
	if (player == BLACK) {
		return tolower(name);
	} else {
		return toupper(name);
	}
}