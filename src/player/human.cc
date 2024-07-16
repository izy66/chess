#include "human.h"
#include "parser.h"
#include "moves/move.h"
#include <iostream>
#include <sstream>

HumanPlayer::HumanPlayer(Board* chess_board, char player) : Player{chess_board, player} {}
HumanPlayer::HumanPlayer(HumanPlayer& other) : Player{other.chess_board, player} {
	parser = std::make_unique<Parser>();
}
HumanPlayer::~HumanPlayer() {}

bool HumanPlayer::MakeMove() {
	std::string readline, command, from, to, promotion;
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
		if (!(ss >> from)) { }
		if (!(ss >> to)) { }
		std::unique_ptr<Move> move;
		if (!(ss >> promotion)) move = parser->ParseCommand(chess_board, from, to);
		else move = parser->ParseCommand(chess_board, from, to, promotion[0]);
		if (move != nullptr && !chess_board->MakeMove(move)) {
			std::cout << "You can't do that move. Please try another one." << std::endl;
		} else {
			moves.emplace(std::move(move));
		}
	} else {
		std::cout << "Invalid command!" << std::endl;
		ss.ignore();
	}
	return 1;
}