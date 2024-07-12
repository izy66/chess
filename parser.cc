#include "parser.h"
#include "moves/move.h"
#include "moves/king_move.h"
#include "moves/pawn_move.h"
// #include "moves/queenmove.h"
// #include "moves/bishopmove.h"
// #include "moves/knightmove.h"
// #include "moves/rookmove.h"

std::unique_ptr<Move> Parser::ParseCommand(ChessBoard* chess_board, std::string& from, std::string& to) {
	// Move move;
	switch (char c = tolower(chess_board->GetPieceName(from))) {
	case 'k':
		return std::make_unique<KingMove>(from, to);
		break;
	case 'p':
		return std::make_unique<PawnMove>(from, to);
		break;
	case 'q':
		return std::make_unique<Move>(from, to);
		break;
	case 'b':
		return std::make_unique<Move>(from, to);
		break;
	case 'n':
		return std::make_unique<Move>(from, to);
		break;
	case 'r':
		return std::make_unique<Move>(from, to);
		break;
	default:
		return nullptr;
		break;
	}
}