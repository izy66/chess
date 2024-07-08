#include "parser.h"
#include "kingmove.h"
#include "pawnmove.h"
#include "queenmove.h"
#include "bishopmove.h"
#include "knightmove.h"
#include "rookmove.h"

std::unique_ptr<Move> Parser::ParseCommand(ChessBoard* chess_board, std::string& from, std::string& to) {
	// Move move;
	switch (char c = tolower(chess_board->GetPieceChar(from))) {
	case 'k':
		return std::make_unique<KingMove>(from, to);
		break;
	case 'p':
		return std::make_unique<PawnMove>(from, to);
		break;
	case 'q':
		return std::make_unique<QueenMove>(from, to);
		break;
	case 'b':
		return std::make_unique<BishopMove>(from, to);
		break;
	case 'n':
		return std::make_unique<KnightMove>(from, to);
		break;
	case 'r':
		return std::make_unique<RookMove>(from, to);
		break;
	default:
		break;
	}
}