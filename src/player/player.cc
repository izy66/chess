#include "player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include "vision.h"

Player::Player(Board* chess_board, char player) : chess_board{chess_board}, player{player}, parser{std::make_unique<Parser>()}, vision{std::make_unique<Vision>(chess_board)} {}

Player::~Player() {}

// void Player::AddPiece(const std::shared_ptr<Piece>& piece) {
// 	hand[piece->Location()] = piece;
// }

// void Player::DiscardHand() {
// 	hand.clear();
// }

// void Player::DiscardPiece(const std::string& loc) {
// 	hand[loc] = nullptr;
// }

void Player::RefreshVision() {
	vision->Refresh(get_hand());
}

int Player::CanSee(const std::string& loc) const {
	return vision->CanSee(loc);
}

bool Player::CanCapture(const std::string& to) const {
	for (const auto& piece : get_hand()) {
		if (piece->CanCover(to)) return 1;
	}
	return 0;
}

std::vector<std::shared_ptr<Piece>> Player::get_hand() const {
	std::vector<std::shared_ptr<Piece>> hand;
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			std::string loc = std::string() + c + r;
			auto piece = (*chess_board)[loc];
			if (piece != nullptr && piece->Player() == player) {
				hand.push_back((*chess_board)[loc]);
			}
		}
	}
	return hand;
}