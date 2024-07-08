#include "parser.h"
#include "kingmove.h"
#include "pawnmove.h"
#include "queenmove.h"
#include "bishopmove.h"
#include "knightmove.h"
#include "rookmove.h"

Move* Parser::ParseCommand(ChessBoard* chess_board, std::string& from, std::string& to) {
	Move *move = nullptr;
	switch (char c = tolower(chess_board->GetPieceChar(from))) {
	case 'k':
		move = new KingMove{from, to};
		break;
	case 'p':
		move = new PawnMove{from, to};
		break;
	case 'q':
		move = new QueenMove{from, to};
		break;
	case 'b':
		move = new BishopMove{from, to};
		break;
	case 'n':
		move = new KnightMove{from, to};
		break;
	case 'r':
		move = new RookMove{from, to};
		break;
	default:
		break;
	}
	return move;
}