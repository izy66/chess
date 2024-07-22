#include "vision.h"
#include "chessboard.h"
#include "player.h"

void Vision::Refresh(std::vector<std::shared_ptr<Piece>> hand) {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			std::string loc = std::string() + c + r;
			vision[loc] = 0;
		}
	}
	for (const auto& piece : hand) {
		for (const auto& move : *piece) {
			++vision[move];
		}
	}
}

int Vision::CanSee(const std::string& loc) {
	return vision[loc];
}