#include "game.h"
#include "chessboard.h"
using namespace std;

int main() {
	ChessBoard chess_board;
	Game chess_game;
	chess_game.Start(&chess_board);
}