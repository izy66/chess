#include "controller.h"
#include "kingmove.h"
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

void Controller::FetchMove() {
	// std::unique_ptr<Move> move = parser->ParseCommand();
	// if (!command->Execute()) return;
	// recent_decision = recent_decision->AddDecision(std::move(command));
}

void Controller::StartGame() {
	while (true) {
		chess_board->Reset();
		if (!RunGame()) break;
		DisplayScores();
	}
}

void Controller::GameOver() {
	player = WHITE;
	opponent = BLACK;
}

bool Controller::RunGame() {
	std::string read_line, command, from, to;
	while (true) {
		chess_board->Print();
		if (player == WHITE) {
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
			if (player == WHITE) {
				BlackWon();
			} else {
				WhiteWon();
			}
			GameOver();
			break;
		} else
		if (command.compare("draw") == 0) {
			Draw();
			GameOver();
			break;
		} else
		if (command.compare("undo") == 0) {
			recent_decision = recent_decision->UndoDecision(chess_board);
		} else 
		if (command.compare("move") == 0) {
			if (!(ss >> from)) { }
			if (!(ss >> to)) { }
			if (chess_board->GetPieceColor(from) != player) {
				std::cout << "You can't move your opponent's pieces! Please make another move." << std::endl;
				continue;
			}
			if (chess_board->Empty(from)) {
				std::cout << "You have to move a piece!" << std::endl;
				continue;
			}
			if (chess_board->GetPieceColor(to) == player) {
				std::cout << "You can't step over your own pieces!" << std::endl;
				continue;
			}
			// moves.emplace(parser->ParseCommand(chess_board, from, to));
			// Move* move = parser->ParseCommand(chess_board, from, to);
			std::unique_ptr<Move> move = parser->ParseCommand(chess_board, from, to);
			if (!chess_board->MakeMove(move)) { // check rules
				std::cout << "You can't do that move. Please try another one." << std::endl;
				continue;
			}
			if (recent_decision == nullptr) {
				std::cout << "nullptr!" << std::endl;
			}
			recent_decision = recent_decision->AddDecision(std::move(move));
			if (chess_board->GameOver()) { // ok, last move is very good
				GameOver();
				break;
			}
		} else {
			std::cout << "Invalid command!" << std::endl;
			continue;
		}
		std::swap(player, opponent);
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
		getline(std::cin, command);
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
			if ((param1[0] == 'P' || param1[0] == 'p') && (param2[1] == TOP_ROW || param2[1] == BOT_ROW)) {
				std::cout << "You can't put pawn on the last line! That's unfair!" << std::endl;
				continue;
			}
			if (isupper(param1[0])) {
				if (param1[0] == 'K' && white_king) {
					std::cout << "You can't put two white kings on the board! That's unfair!" << std::endl;
				} else {
					chess_board->SetPiece(param2, param1[0], WHITE);
					if (param1[0] == 'K') white_king = true;
				}
			} else {
				if (param1[0] == 'k' && black_king) {
					std::cout << "You can't put two black kings on the board! That's unfair!" << std::endl;
				} else {
					chess_board->SetPiece(param2, param1[0], BLACK);
					if (param1[0] == 'k') black_king = true;
				}
			}
		} else 
		if (option.compare("-") == 0) {
			if (!(ss >> param1)) { }
			char cur_piece = chess_board->GetPieceChar(param1);
			chess_board->RemovePiece(param1); // if fails, doesn't affect king's flag
			if (cur_piece == 'K') white_king = false;
			if (cur_piece == 'k') black_king = false;
		} else 
		if (option.compare("=") == 0) {
			if (!(ss >> param1)) { }
			// param1 = tolower(param1);
			if (param1.compare("white") == 0) {
				WhiteMovesNext();
			} else
			if (param1.compare("black") == 0) {
				BlackMovesNext();
			}
		} else {
			std::cout << "invalid command." << std::endl;
		}
	}

	std::cout << "Setup complete." << std::endl;

	RunGame();
}