#include "human_player.h"
#include "parser.h"
#include "moves/move.h"
#include "vision.h"
#include <iostream>
#include <sstream>

void HumanPlayer::TakeAction() {
	std::string readline, command;
	if (!getline(std::cin, readline)) throw _end_of_line_{};
	std::stringstream ss{readline};
	ss >> command;
	if (command.compare("resign") == 0) {
		chess_board->PlayerResign();
	} else
	if (command.compare("draw") == 0) {
		chess_board->Draw();
	} else
	if (command.compare("undo") == 0) {
		try {
			chess_board->Undo();
		} catch (...) {
			throw;
		}
	} else 
	if (command.compare("move") == 0) {
		from = to = promotion = "";
		if (!(ss >> from)) { 
			throw _parsing_error_{"Missing first coordinate."}; 
		}
		if (!(ss >> to)) { 
			throw _parsing_error_{"Missing second coordinate."}; 
		}
		if (chess_board->Empty(from)) { 
			throw _invalid_move_{"You should move a piece!"}; 
		}
		if (chess_board->GetPiecePlayer(from) != player) { 
			throw _invalid_move_{"You should move one of your pieces!"}; 
		}
		if (from == to) { 
			throw _invalid_move_{"You should move to a different square!"}; 
		}
		if (chess_board->GetPiecePlayer(to) == player) { 
			throw _invalid_move_{"You can't step over your own pieces!"}; 
		}
		if ((*chess_board)[from]->CanPromote()) {
			if (!(ss >> promotion)) {
				throw _parsing_error_{"Missing pawn promotion."}; 
			}
			if (toupper(promotion[0]) == KING || toupper(promotion[0]) == PAWN) {
				throw _invalid_move_{"You should promote your pawn to a Queen, Bishop, Rook, or Knight only."};
			}
		}
		try {
			MakeMove();
			vision->Refresh(chess_board->GetHand(player));
		} catch (...) {
			throw;
		}
	} else {
		throw _parsing_error_{"Player action is unknown. Please try again."};
	}
}

void HumanPlayer::MakeMove() {
	std::unique_ptr<AbstractMove> move;
	if (promotion.empty()) {
		move = parser->ParseCommand(chess_board, from, to);
	} else {
		move = parser->ParseCommand(chess_board, from, to, promotion[0]);
	}
	try {
		chess_board->MakeMove(std::move(move));
	} catch (...) {
		throw;
	}
}