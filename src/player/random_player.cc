#include "random_player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>

RandomPlayer::RandomPlayer(Board* board, char player) : Player{board, player} {}

bool RandomPlayer::MakeMove() {
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
		std::vector<std::string> my_pieces;
		for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
			for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
				std::string loc = std::string() + c + r;
				if (chess_board->GetPiecePlayer(loc) == player && chess_board->CanMove(loc)) {
					my_pieces.push_back(loc);				
				}
			}
		}
		while (true) {
			srand(time(NULL));
			std::string from = my_pieces[rand() % my_pieces.size()];
			std::string to = chess_board->MakeRandomMove(from);
			std::unique_ptr<Move> random_move = parser->ParseCommand(chess_board, from, to);
			chess_board->MakeMove(random_move);
			moves.emplace(std::move(random_move));
			break;
		}
	} else {
		std::cout << "Invalid command!" << std::endl;
		ss.ignore();
	}
	return 1;
}