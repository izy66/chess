#include "player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include "vision.h"

Player::Player(Board* chess_board, char player) : chess_board{chess_board}, player{player}, parser{std::make_unique<Parser>()}, vision{std::make_unique<Vision>()} {}

Player::~Player() {}

void Player::RefreshVision() {
	vision->Refresh(chess_board->GetHand(player));
}

int Player::CanSee(const std::string& loc) const {
	return vision->CanSee(loc);
}

bool Player::CanCapture(const std::string& to) const {
	for (const auto& piece : chess_board->GetHand(player)) {
		if (piece->CanCover(to)) return true;
	}
	return false;
}

std::unique_ptr<AbstractMove> Player::ParseCommand(const std::string& from, const std::string& to, char promotion) noexcept {
	return parser->ParseCommand(chess_board, from, to, promotion);
}
