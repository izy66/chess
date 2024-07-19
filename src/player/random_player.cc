#include "random_player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>

RandomPlayer::RandomPlayer(Board* chess_board, char player) : ComputerPlayer{chess_board, player} {}

void RandomPlayer::MakeMove() {
	while (true) {
		srand(time(NULL));
		auto rand_piece = hand[rand() % hand.size()];
		std::string to = chess_board->MakeRandomMove(rand_piece);
		if (to.empty()) continue;
		auto move = parser->ParseCommand(chess_board, rand_piece->Location(), to);
		try {
			chess_board->MakeMove(std::move(move));
		} catch (...) {
			throw;
		}
	}
}