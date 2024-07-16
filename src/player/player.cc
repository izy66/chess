#include "player.h"
#include "parser.h"
#include "board.h"
#include "moves/move.h"

Player::Player(Board* chess_board, char player) : chess_board{chess_board}, player{player}, parser{std::make_unique<Parser>()} {}
Player::~Player() {}

bool Player::Undo() { 
	if (!moves.top()->Undo(chess_board)) return 0;
	moves.pop(); 
	return 1;
}