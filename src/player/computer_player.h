#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include "pieces/piece.h"
#include "player.h"
#include "beginner_player.h"
#include "random_player.h"

class Board;

class ComputerPlayer final : public Player {

	friend class BeginnerPlayer;
	friend class RandomPlayer;
	
	int level;
	RandomPlayer rand_player;
	BeginnerPlayer begin_player;

	protected:

		static const int NUM_PIECE = 6;
		const char piece_rank[NUM_PIECE] = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
		int get_rank(char c) const { for (int i = 0; i < 6; ++i) if (piece_rank[i] == c) return i; return -1; }

	public:
		ComputerPlayer(Board* chess_board, char player, int level) : Player{chess_board, player}, level{level}, rand_player{chess_board, player}, begin_player{chess_board, player} { is_human = false; }
		
		virtual ~ComputerPlayer() {}

		void TakeAction() override;
		void MakeMove() override;

		void BeginnerMakeMove();
		void RandMakeMove();
};

#endif