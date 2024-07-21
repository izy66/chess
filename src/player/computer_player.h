#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include "pieces/piece.h"
#include "player.h"
#include "computer_level_1.h"
#include "computer_level_2.h"
#include "computer_level_3.h"
#include "computer_level_4.h"

class Board;

class ComputerPlayer final : public Player {

	friend class ComputerLevel1;
	friend class ComputerLevel2;
	friend class ComputerLevel3;
	friend class ComputerLevel4;
	
	int level;
	ComputerLevel1 level_1;
	ComputerLevel2 level_2;
	ComputerLevel3 level_3;
	ComputerLevel4 level_4;

	protected:

		static const int NUM_PIECE = 6;
		const char piece_rank[NUM_PIECE] = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
		int get_rank(char c) const { for (int i = 0; i < 6; ++i) if (piece_rank[i] == toupper(c)) return i; return -1; }

	public:
		ComputerPlayer(Board*, char, int);
		
		virtual ~ComputerPlayer() {}

		void TakeAction() override;
		void MakeMove() override;
};

#endif