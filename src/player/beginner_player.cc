#include "beginner_player.h"
#include "board.h"
#include "parser.h"
#include "moves/move.h"

bool BeginnerPlayer::MakeMove(Board* chess_board) {
	int highest_rank = -1;
	std::string capture_move_from = "", capture_move_to = "", check_move_from = "", check_move_to = "";
	for (size_t rank = 0; rank < NUM_PIECE; ++rank) {
		for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
			for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
				std::string from = std::string() + c + r;
				if (chess_board->GetPiecePlayer(from) == player && 
						get_rank(toupper(chess_board->GetPieceName(from))) == rank) {
					std::string capture_move = chess_board->BestCaptureMove(from);
					int captured_rank = get_rank(toupper(chess_board->GetPieceName(capture_move)));
					if (!capture_move.empty() && captured_rank > rank) {
						highest_rank = captured_rank;
						capture_move_from = from;
						capture_move_to = capture_move;
					}
					if (check_move_to.empty()) {
						check_move_from = from;
						check_move_to = chess_board->TryCheckMove(from);
					}
				}
			}
		}
	}
	if (!capture_move_to.empty()) {
		std::unique_ptr<Move> capture_move = parser->ParseCommand(chess_board, capture_move_from, capture_move_to);
		chess_board->MakeMove(capture_move);
		// moves.emplace(std::move(random_move));
		return 1;
	} else
	if (!check_move_to.empty()) {
		std::unique_ptr<Move> check_move = parser->ParseCommand(chess_board, check_move_from, check_move_to);
		chess_board->MakeMove(check_move);
		// moves.emplace(std::move(random_move));
		return 1;

	}
	return base_player->MakeMove(chess_board);
}