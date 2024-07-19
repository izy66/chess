#include "controller.h"
#include "pieces/piece.h"
#include <iostream>
#include <sstream>

#define HUMAN_PLAYER "human"
#define COMPUTER_LEVEL1 "computer1"
#define COMPUTER_LEVEL2 "computer2"
#define COMPUTER_LEVEL3 "computer3"
#define COMPUTER_LEVEL4 "computer4"

Controller::~Controller() { 
	std::cout << "Final Score:" << std::endl;
	chess_board->DisplayScores();
}

void Controller::StartGame() {
	std::string command, mode, player1, player2;
	chess_board->Reset();
	while (true) {
		if (!getline(std::cin, command)) {
			break;
		}
		std::stringstream ss{command};
		ss >> mode;
		if (mode.compare("setup") == 0) {
			Setup();
		} else
		if (mode.compare("game") == 0) {
			if (!(ss >> player1)) {}
			if (!(ss >> player2)) {}
			if (player1.compare(HUMAN_PLAYER) == 0) {
				chess_board->AddHumanPlayer(WHITE);
			} else
			if (player1.compare(COMPUTER_LEVEL1) == 0) {
				chess_board->AddComputerPlayer(WHITE, 1);
			} else
			if (player1.compare(COMPUTER_LEVEL2) == 0) {
				chess_board->AddComputerPlayer(WHITE, 2);
			}
			if (player2.compare(HUMAN_PLAYER) == 0) {
				chess_board->AddHumanPlayer(BLACK);
			} else
			if (player2.compare(COMPUTER_LEVEL1) == 0) {
				chess_board->AddComputerPlayer(BLACK, 1);
			} else
			if (player2.compare(COMPUTER_LEVEL2) == 0) {
				chess_board->AddComputerPlayer(BLACK, 2);
			}
			while (true) {
				try {
					RunGame();
				} catch (_end_of_line_& eol) {
					break;
				} catch (...) {
					continue;
				}
			}
		} 
	}
}

void Controller::GameOver() {
	std::cout << "Current Score:" << std::endl;
	chess_board->DisplayScores();
	chess_board->Reset();
}

void Controller::RunGame() {
	chess_board->Print();
	while (true) {
		if (chess_board->GameOver()) { // ok, last move was very good
			GameOver();
			return;
		}
		try {
			chess_board->PlayerMakeMove();
		} catch (_end_of_line_& eol) {
			throw;
		} catch (...) {
			continue;
		}
	}
}

void Controller::Setup() {
	std::cout << "Entering setup mode." << std::endl;
	chess_board->Clear();

	std::string command, option, param1, param2;

	while (true) {
		chess_board->Print();
		if (!getline(std::cin, command)) {
			break;
		}
		std::stringstream ss{command};
		ss >> option;
		if (option.compare("done") == 0) {
			try {
				chess_board->SetUpDone();
				break;
			} catch (...) {
				continue;;
			}
		} else 
		if (option.compare("+") == 0) {
			if (!(ss >> param1)) { }
			if (!(ss >> param2)) { }
			try {
				if (isupper(param1[0])) {
					chess_board->SetPiece(param2, param1[0], WHITE);
				} else {
					chess_board->SetPiece(param2, param1[0], BLACK);
				}
			} catch(...) {
				continue;
			}
		} else 
		if (option.compare("-") == 0) {
			if (!(ss >> param1)) { }
			chess_board->RemovePiece(param1);
		} else 
		if (option.compare("=") == 0) {
			if (!(ss >> param1)) { }
			chess_board->PlayerMovesNext(param1[0]);
		} else {
			_parsing_error_{"Setup command unknown."};
		}
	}

	std::cout << "Setup complete." << std::endl;
}