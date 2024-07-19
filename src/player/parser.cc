#include "parser.h"
#include "moves/move.h"
#include "moves/king_move.h"
#include "moves/pawn_move.h"
#include <iostream>

std::unique_ptr<Move> Parser::ParseCommand(Board* chess_board, const std::string& from, const std::string& to, char promotion) noexcept {
	// Move move;
	switch (char c = toupper(chess_board->GetPieceName(from))) {
	case KING:
		return std::make_unique<KingMove>(from, to);
	case PAWN:
		return std::make_unique<PawnMove>(from, to, promotion);
	case QUEEN:
		return std::make_unique<Move>(from, to);
	case BISHOP:
		return std::make_unique<Move>(from, to);
	case KNIGHT:
		return std::make_unique<Move>(from, to);
	case ROOK:
		return std::make_unique<Move>(from, to);
	default:
		return nullptr;
	}
}