#include "computer_player.h"
#include "parser.h"
#include "board.h"
// #include "moves/move.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>

int rand_n(int n) {
	srand(time(NULL));
	return rand() % n;
}

void ComputerLevel1::MakeMove(ComputerPlayer* player) {
	while (true) {
		auto hand = player->chess_board->GetHand(player->player);
		auto piece = hand[rand_n(hand.size())];
		// make a random move
		int count_moves = 0;

		for (const auto& to : *piece) {

			if (piece->CanMove(to) && (!piece->CanGetCaptured(to) || piece->CapturedRank(to) >= piece->Priority())) ++count_moves;
		}

		if (count_moves == 0) continue; // no valid moves

		int rand_move = rand_n(count_moves) + 1;

		for (const auto& to: *piece) {

			if (piece->CanMove(to) && (!piece->CanGetCaptured(to) || piece->CapturedRank(to) >= piece->Priority())) --rand_move;
			if (rand_move == 0) {

				auto next_move = player->ParseCommand(piece->Location(), to);
				
				try {
					player->chess_board->MakeMove(std::move(next_move));
					return;
				} catch (...) {
					throw;
				}
			}
		}
	}
}