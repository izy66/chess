#include "parser.h"
#include "moves/move.h"
#include "moves/king_move.h"
#include "moves/pawn_move.h"
#include <iostream>

std::unique_ptr<Move> Parser::ParseCommand(ChessBoard* chess_board, std::string& from, std::string& to, char promotion) {
	// Move move;
	switch (char c = tolower(chess_board->GetPieceName(from))) {
	case 'k':
		return std::make_unique<KingMove>(from, to);
		break;
	case 'p':
		if (chess_board->CanPromote(from) && toupper(promotion) == PAWN) {
			std::cout << "You have to promote your pawn!" << std::endl;
			return nullptr;
		}
		return std::make_unique<PawnMove>(from, to, promotion);
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
		std::cout << "You need to move a piece on the board!" << std::endl;
		return nullptr;
		break;
	}
}