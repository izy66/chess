#include "player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"

Player::Player(char player) : player{player}, parser{std::make_unique<Parser>()} {}

Player::~Player() {}

bool Player::TakeAction(Board* chess_board) {
	if (!take_action(chess_board)) return 0;
	if (!make_move) return 1;
	return MakeMove(chess_board);
}

bool Player::Undo(Board* chess_board) { 
	if (!moves.top()->Undo(chess_board)) return 0;
	moves.pop(); 
	return 1;
}