#include "computer_player.h"
#include "board.h"
#include "parser.h"
#include "moves/abstract_move.h"

int ComputerLevel4::alpha_beta_max(ComputerPlayer* comp_player, int level, int alpha, int beta) {
	if (level == 0) {
		return board->BoardScore();
	}
	// make a move, then select one that yields max return if player is white, or min if black
	int best_score = - Board::MAX_SCORE - 1;
	// comp_player->RefreshVision();
	for (const auto& piece : board->GetHand(comp_player->player)) {
		for (auto move  = piece->begin(); move != piece->end(); ++move) {
			if (piece->CanMove(*move)) {
				board->ApplyMove(comp_player->ParseCommand(piece->Location(), *move));
				board->PlayerMovesNext(opponent);
				best_score = std::max(best_score, alpha_beta_min(comp_player, level - 1, alpha, beta));
				board->PlayerMovesNext(player);
				board->Undo();
				if (best_score > beta) return best_score;
				if (alpha < best_score) {
					alpha = best_score;
					best_from = piece->Location();
					best_move = *move;
				}
			}
		}
	}
	return best_score;
}

int ComputerLevel4::alpha_beta_min(ComputerPlayer* comp_player, int level, int alpha, int beta) {
	if (level == 0) {
		return board->BoardScore();
	}
	// make a move, then select one that yields max return if player is white, or min if black
	int best_score = Board::MAX_SCORE + 1;
	// comp_player->RefreshVision();
	for (const auto& piece : board->GetHand(comp_player->player)) {
		for (auto move  = piece->begin(); move != piece->end(); ++move) {
			if (piece->CanMove(*move)) {
				board->ApplyMove(comp_player->ParseCommand(piece->Location(), *move));
				board->PlayerMovesNext(player);
				best_score = std::min(best_score, alpha_beta_max(comp_player, level - 1, alpha, beta));
				board->PlayerMovesNext(opponent);
				board->Undo();
				if (best_score < alpha) return best_score;
				beta = std::min(beta, best_score);
			}
		}
	}
	return best_score;
}

void ComputerLevel4::MakeMove(ComputerPlayer* comp_player) {

	// if (++move_count < 4) throw _no_moves_found_{};

	player = comp_player->player;
	opponent = player == WHITE ? BLACK : WHITE;
	
	alpha_beta_max(comp_player, 2, -Board::MAX_SCORE - 1, Board::MAX_SCORE + 1);
	
	try {
		board->MakeMove(comp_player->ParseCommand(best_from, best_move));
		return;
	} catch (...) {
		throw;
	}

	throw _no_moves_found_{};
}
