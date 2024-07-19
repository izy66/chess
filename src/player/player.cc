#include "player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"
#include "vision.h"

Player::Player(Board* chess_board, char player) : chess_board{chess_board}, player{player}, parser{std::make_unique<Parser>()}, vision{std::make_unique<Vision>(chess_board, this)} {}

Player::~Player() {}

void Player::AddPiece(const std::shared_ptr<Piece>& piece) {
	hand.push_back(piece);
}

void Player::DiscardHand() {
	hand.clear();
}

void Player::RefreshVision() {
	vision->Refresh();
}

int Player::CanSee(const std::string& loc) const {
	return vision->CanSee(loc);
}