#include "random_player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>

RandomPlayer::RandomPlayer(char player) : ComputerPlayer{player} {}

bool RandomPlayer::MakeMove(Board* chess_board) {
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
		return 1;
	}
	return 0;
}