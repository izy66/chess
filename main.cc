#include "chessboard.h"
using namespace std;

int main() {
	ChessBoard chess;
	chess.Reset();
	// chess.SetPiece("e2", 'k', WHITE);
	// chess.RemovePiece("e1");
	chess.Print();
}