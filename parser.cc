#include "parser.h"
#include "kingmove.h"
#include "pawnmove.h"

Move* Parser::ParseCommand(ChessBoard* chess_board, std::string& from, std::string& to) {
	Move *move;
	switch (char c = tolower(chess_board->GetPieceChar(from))) {
	case 'k':
		move = new KingMove{from, to};
		break;
	case 'p':
		move = new PawnMove{from, to};
	default:
		break;
	}
	return move;
}