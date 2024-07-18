#include "computer_player.h"
#include "board.h"

bool ComputerPlayer::take_action(Board* chess_board) {
	std::string readline, command;
	if (!getline(std::cin, readline)) return 0;
	std::stringstream ss{readline};
	ss >> command;
	make_move = 0;
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
		make_move = 1;
	} else {
		std::cout << "Invalid player action!" << std::endl;
		ss.ignore();
	}
	return 1;
}