#include "random_player.h"
#include "computer_player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>

RandomPlayer::RandomPlayer(Board* chess_board, char player) : chess_board{chess_board}, player{player} {}

int rand_n(size_t n) {
	srand(time(NULL));
	return rand() % n;
}

void RandomPlayer::MakeMove(ComputerPlayer* player) {
	while (true) {
		auto hand = player->get_hand();
		auto piece = hand[rand_n(hand.size())];
		// make a random move
		int count_moves = 0;
		Piece::Iterator iter = piece->begin();
		while (iter != piece->end()) {
			++iter;
			if (piece->CanMove(*iter)) ++count_moves;
		}
		if (count_moves == 0) continue; // no valid moves
		int rand_move = rand_n(count_moves) + 1;
		iter = piece->begin();
		while (rand_move) {
			++iter;
			if (piece->CanMove(*iter)) --rand_move;
		}
		auto to = *iter;
		auto move = player->parser->ParseCommand(chess_board, piece->Location(), to);
		try {
			chess_board->MakeMove(std::move(move));
			return;
		} catch (...) {
			throw;
		}
	}
}