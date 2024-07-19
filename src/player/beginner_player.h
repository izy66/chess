#ifndef COMPUTER_LEVEL_2
#define COMPUTER_LEVEL_2

#include "advanced_computer.h"

class BeginnerPlayer final: public AdvancedComputer {
	public:
		BeginnerPlayer(std::shared_ptr<Player> base_player, Board* chess_board, char player) : AdvancedComputer{base_player, chess_board, player} {}
	
		void MakeMove() override;
};

#endif