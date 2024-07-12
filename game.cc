#include "game.h"
#include "textui.h"
#include "controller.h"
#include <iostream>

void Game::Start(ChessBoard* game_board) {
	TextUI ui{game_board};
	Controller controller{game_board};
	// controller.Setup();
	controller.StartGame();
}

