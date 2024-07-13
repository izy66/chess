#include "controller.h"
#include "pieces/piece.h"
#include <iostream>
#include <sstream>

Controller::~Controller() { 
	DisplayFinalScores();
}

void Controller::DisplayScores() {
	std::cout << "Current Score:" << std::endl;
	std::cout << "White: " << white_score << std::endl;
	std::cout << "Black: " << black_score << std::endl;
}

void Controller::DisplayFinalScores() {
	std::cout << "Final Score:" << std::endl;
	std::cout << "White: " << white_score << std::endl;
	std::cout << "Black: " << black_score << std::endl;
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
			while (RunGame());
		} else
		if (mode.compare("quit") == 0) {
			return;
		}
	}
}

void Controller::GameOver() {
	if (chess_board->WhoWon() == WHITE) ++white_score;
	else if (chess_board->WhoWon() == BLACK) ++black_score;
	else if (chess_board->WhoWon() == DRAW) {
		white_score += 0.5;
		black_score += 0.5;
	}
	DisplayScores();
	chess_board->Reset();
}

bool Controller::RunGame() {
	std::string read_line, command, from, to, promotion;
	while (true) {
		if (chess_board->GameOver()) { // ok, last move is very good
			GameOver();
			break;
		}
		chess_board->Print();
		if (chess_board->Player() == WHITE) {
			std::cout << "White to move." << std::endl;
		} else {
			std::cout << "Black to move." << std::endl;
		}
		if (!getline(std::cin, read_line)) {
			return 0;
		}
		std::stringstream ss{read_line};
		ss >> command;
		if (command.compare("resign") == 0) {
			if (chess_board->Player() == WHITE) {
				BlackWon();
			} else {
				WhiteWon();
			}
			GameOver();
			return 1;
		} else
		if (command.compare("draw") == 0) {
			Draw();
			GameOver();
			return 1;
		} else
		if (command.compare("undo") == 0) {
			recent_decision = recent_decision->UndoDecision(chess_board);
		} else 
		if (command.compare("move") == 0) {
			if (!(ss >> from)) { }
			if (!(ss >> to)) { }
			std::unique_ptr<Move> move;
			if (!(ss >> promotion)) move = parser->ParseCommand(chess_board, from, to);
			else move = parser->ParseCommand(chess_board, from, to, promotion[0]);
			if (move == nullptr) continue;
			if (!chess_board->MakeMove(move)) { // check rules
				std::cout << "You can't do that move. Please try another one." << std::endl;
				continue;
			}
			recent_decision = recent_decision->AddDecision(std::move(move));
		} else {
			std::cout << "Invalid command!" << std::endl;
			ss.ignore();
			continue;
		}
	}
	return 1;
}

void Controller::Setup() {
	std::cout << "Entering setup mode." << std::endl;
	chess_board->Clear();

	bool white_king = false, black_king = false;
	std::string command, option, param1, param2;

	while (true) {
		chess_board->Print();
		if (!getline(std::cin, command)) {
			break;
		}
		std::stringstream ss{command};
		ss >> option;
		if (option.compare("done") == 0) {
			if (!white_king) {
				std::cout << "You need a white king on board." << std::endl;
				continue;
			}
			if (!black_king) {
				std::cout << "You need a black king on board." << std::endl;
				continue;
			}
			break;
		} else 
		if (option.compare("+") == 0) {
			if (!(ss >> param1)) { }
			if (!(ss >> param2)) { }
			if (toupper(param1[0]) == PAWN && (param2[1] == TOP_ROW || param2[1] == BOT_ROW)) {
				std::cout << "You can't put pawn on the last line! That's unfair!" << std::endl;
				continue;
			}
			if (isupper(param1[0])) {
				if (param1[0] == toupper(KING) && white_king) {
					std::cout << "You can't put two white kings on the board! That's unfair!" << std::endl;
				} else {
					chess_board->SetPiece(param2, param1[0], WHITE);
					if (param1[0] == KING) white_king = true;
				}
			} else {
				if (param1[0] == tolower(KING) && black_king) {
					std::cout << "You can't put two black kings on the board! That's unfair!" << std::endl;
				} else {
					chess_board->SetPiece(param2, param1[0], BLACK);
					if (param1[0] == tolower(KING)) black_king = true;
				}
			}
		} else 
		if (option.compare("-") == 0) {
			if (!(ss >> param1)) { }
			char cur_piece = chess_board->GetPieceName(param1);
			chess_board->RemovePiece(param1); // if fails, doesn't affect king's flag
			if (cur_piece == KING) white_king = false;
			if (cur_piece == tolower(KING)) black_king = false;
		} else 
		if (option.compare("=") == 0) {
			if (!(ss >> param1)) { }
			chess_board->PlayerMovesNext(param1[0]);
		} else {
			std::cout << "invalid command." << std::endl;
		}
	}

	std::cout << "Setup complete." << std::endl;
}