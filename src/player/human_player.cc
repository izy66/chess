#include "human_player.h"
#include "parser.h"
#include "moves/move.h"
#include <iostream>
#include <sstream>

HumanPlayer::HumanPlayer(char player) : Player{player} { is_human = true; }
HumanPlayer::HumanPlayer(HumanPlayer& other) : Player{player} {
	parser = std::make_unique<Parser>();
}
HumanPlayer::~HumanPlayer() {}

bool HumanPlayer::take_action(Board* chess_board) {
	std::string readline, command;
	if (!getline(std::cin, readline)) return 0;
	std::stringstream ss{readline};
	ss >> command;
	if (command.compare("resign") == 0) {
		chess_board->PlayerResign();
	} else
	if (command.compare("draw") == 0) {
		chess_board->Draw();
	} else
	if (command.compare("undo") == 0) {
		chess_board->Undo();
	} else 
	if (command.compare("move") == 0) {
		from = to = promotion = "";
		if (!(ss >> from)) {}
		if (!(ss >> to)) {}
		if (!(ss >> promotion)) {}
		make_move = 1;
	} else {
		std::cout << "Invalid player action!" << std::endl;
		ss.ignore();
	}
	return 1;
}

bool HumanPlayer::MakeMove(Board* chess_board) {
	std::unique_ptr<Move> move;
	if (promotion.empty()) move = parser->ParseCommand(chess_board, from, to);
	else move = parser->ParseCommand(chess_board, from, to, promotion[0]);
	if (move != nullptr && !chess_board->MakeMove(move)) {
		std::cout << "You can't do that move. Please try another one." << std::endl;
		return 0;
	} else {
		moves.emplace(std::move(move));
	}
	return 1;
}