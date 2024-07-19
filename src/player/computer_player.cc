#include "computer_player.h"
#include "board.h"
#include "vision.h"

void ComputerPlayer::TakeAction() {
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
		chess_board->Undo();
	} else 
	if (command.compare("move") == 0) {
		try {
			MakeMove();
			vision->Refresh();
		} catch (...) {
			throw;
		}
	} else {
		throw _parsing_error_{"Player action is invalid."};
	}
}