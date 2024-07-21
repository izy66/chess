#include "computer_player.h"
#include "computer_level_3.h"
#include "board.h"
#include "parser.h"
#include "moves/abstract_move.h"

void ComputerLevel3::MakeMove(ComputerPlayer* player) {
	int highest_rank = 0;
	std::string escape_from = "", escape_to = "";

	for (const auto& piece : player->chess_board->GetHand(player->player)) {

		if (piece->CanGetCaptured(piece->Location()) && piece->Priority() >= highest_rank) {

			auto from = piece->Location();

			for (const auto& to : *piece) {
				if (!escape_to.empty()) break;
				if (!piece->CanMove(to)) continue;

				player->chess_board->ApplyMove(player->ParseCommand(from, to));

				if (!piece->CanGetCaptured(piece->Location())) {

					highest_rank = piece->Priority();
					escape_from = from;
					escape_to = to;
				}

				player->chess_board->Undo();
			}

		}
	}

	if (!escape_to.empty()) {
		try {
			player->chess_board->MakeMove(player->ParseCommand(escape_from, escape_to));
			return;
		} catch (...) {
			throw;
		}
	}
	
	throw _no_moves_found_{};
}
