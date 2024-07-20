#include "vision.h"
#include "chessboard.h"
#include "player.h"

Vision::Vision(Board* chess_board) : chess_board{chess_board} {}

void Vision::Refresh(std::vector<std::shared_ptr<Piece>> hand) {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			std::string loc = std::string() + c + r;
			vision[loc] = 0;
		}
	}
	for (const auto& piece : hand) {
		Piece::Iterator visible_block = piece->begin();
		++visible_block;
		for (; visible_block != piece->end(); ++visible_block) {
			++vision[*visible_block];
		}
	}
}

int Vision::CanSee(const std::string& loc) {
	return vision[loc];
}