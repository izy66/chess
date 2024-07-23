#include "shogi_player.h"
#include "player/parser.h"
#include "moves/move.h"
#include "player/vision.h"
#include "shogi/move/drop.h"
#include <iostream>
#include <sstream>

void ShogiPlayer::TakeAction() {
	std::string readline, command;
	if (!getline(std::cin, readline)) throw _end_of_line_{};
	std::stringstream ss{readline};
	ss >> command;
	if (command.compare("resign") == 0) {
		board->PlayerResign();
	} else
	if (command.compare("draw") == 0) {
		board->Draw();
	} else
	if (command.compare("undo") == 0) {
		try {
			board->Undo();
		} catch (...) {
			throw;
		}
	} else
	if (command.compare("drop") == 0) {
		if (!(ss >> drop_loc)) {
			throw _parsing_error_{"Missing drop location!"};
		}
		std::string name;
		if (!(ss >> name)) {
			throw _parsing_error_{"Missing piece's name!"};
		}
		drop_name = name[0];
		try {
			board->MakeMove(std::make_unique<Drop>(drop_loc, drop_name, player));
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
		if (board->Empty(from)) { 
			throw _invalid_move_{"You should move a piece!"}; 
		}
		if (board->GetPiecePlayer(from) != player) { 
			throw _invalid_move_{"You should move one of your pieces!"}; 
		}
		if (from == to) { 
			throw _invalid_move_{"You should move to a different square!"}; 
		}
		if (board->GetPiecePlayer(to) == player) { 
			throw _invalid_move_{"You can't step over your own pieces!"}; 
		}
		try {
			MakeMove();
			vision->Refresh(board, player);
		} catch (...) {
			throw;
		}
	} else {
		throw _parsing_error_{"Player action is unknown. Please try again."};
	}
}

void ShogiPlayer::MakeMove() {
	std::unique_ptr<AbstractMove> move;
	try {
		board->MakeMove(std::make_unique<Move>(from, to));
	} catch (...) {
		throw;
	}
}