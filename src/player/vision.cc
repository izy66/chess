#include "vision.h"
#include "chessboard.h"
#include "player.h"

void Vision::Refresh(Board* board, char player) {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			std::string loc = std::string() + c + r;
			vision[loc] = 0;
		}
	}
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			auto loc = std::string() + c + r;
			
			if (board->GetPiecePlayer(loc) == player) {

				for (const auto& move : *(*board)[loc]) {
					++vision[move];
				}
			}
		}
	}
}

int Vision::CanSee(const std::string& loc) {
	return vision[loc];
}