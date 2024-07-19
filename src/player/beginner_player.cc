#include "beginner_player.h"
#include "board.h"
#include "parser.h"
#include "moves/move.h"

void BeginnerPlayer::MakeMove() {
	int highest_rank = -1, lowest_rank = NUM_PIECE;
	std::string checkmate_move_from = "", checkmate_move_to = "";
	std::string stalemate_move_from = "", stalemate_move_to = "";
	std::string capture_move_from = "", capture_move_to = "";
	std::string check_move_from = "", check_move_to = "";
	std::string move_from = "", move_to = "";
	for (const auto& piece : *this) {
		std::string from = piece->Location();
		std::string capture_move = chess_board->BestCaptureMove(piece);
		int captured_rank = get_rank(toupper(chess_board->GetPieceName(capture_move)));
		if (!capture_move.empty() && captured_rank > highest_rank) {
			highest_rank = captured_rank;
			capture_move_from = from;
			capture_move_to = capture_move;
		}
		// if (checkmate_move_to.empty()) {
		// 	checkmate_move_from = from;
		// 	checkmate_move_to = chess_board->TryCheckMate(piece);
		// }
		// if (check_move_to.empty()) {
		// 	check_move_from = from;
		// 	check_move_to = chess_board->TryCheckMove(piece);
		// }
	}
	std::unique_ptr<Move> move = nullptr;
	if (!check_move_to.empty()) {
		move = parser->ParseCommand(chess_board, check_move_from, check_move_to);
	} else 
	if (!capture_move_to.empty()) {
		move = parser->ParseCommand(chess_board, capture_move_from, capture_move_to);
	} else 
	if (!check_move_to.empty()) {
		move = parser->ParseCommand(chess_board, check_move_from, check_move_to);
	}
	if (move != nullptr) {
		try {
			chess_board->MakeMove(std::move(move));
			return;
		} catch (...) {
			
		}
	}
	try {
		base_player->MakeMove();
	} catch (...) {
		throw;
	}
}