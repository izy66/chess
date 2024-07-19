#ifndef ADVANCED_COMPUTER
#define ADVANCED_COMPUTER

#include "computer_player.h"
#include "pieces/piece.h"
#include <memory>

class AdvancedComputer : public ComputerPlayer {
	protected:
		std::shared_ptr<Player> base_player;
	
		static const int NUM_PIECE = 6;
		const char piece_rank[NUM_PIECE] = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
		int get_rank(char c) const { for (int i = 0; i < 6; ++i) if (piece_rank[i] == c) return i; return -1; }
	
	public:
		AdvancedComputer(std::shared_ptr<Player> base_player, Board* chess_board, char player) : ComputerPlayer{chess_board, player}, base_player{base_player} {}
};

#endif