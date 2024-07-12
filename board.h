#ifndef BOARD_H
#define BOARD_H

#include "pieces/blank.h"
#include "pieces/piece.h"
#include "subject.h"
#include <vector>
#include <memory>
#include <map>
#include <stack>

#define BLANK nullptr
#define FOG '?'

class Move;

class Board : public Subject {
	protected:
		std::map<std::string, std::unique_ptr<Piece>> pieces;
		std::stack<std::unique_ptr<Piece>> captured_pieces;
		std::map<char, std::vector<char>> captured_by;
		Blank blank;
		std::map<char, std::map<std::string, int>> visibility_counter;

		char player = WHITE, opponent = BLACK;
		std::map<char, std::string> king_loc;
		bool game_over = false, captured = false;
		std::string last_moved;

		/* internal state refreshers */
		void refresh_vision();

	public:
		/* general interface */
		bool Empty(const std::string& loc) { return pieces[loc] == BLANK; }
		bool SetPiece(const std::string& loc, char name, char col);
		bool RemovePiece(const std::string& loc);
		virtual char GetPieceName(const std::string& loc); // overwritten in Fog of War
		char GetPiecePlayer(const std::string& loc);

		virtual void Reset(); // overwritten in Horde, 960
		void Clear();
		void Print() { 
			refresh_vision();
			NotifyObservers(); 
		}

		bool GameOver() { return game_over; }

		/* action interface */
		bool ValidMove(const std::string& from, const std::string& to);
		bool MakeMove(std::unique_ptr<Move>& move);
		bool MovePiece(const std::string& from, const std::string& to);
		void JustMoved(const std::string& loc) { pieces[loc]->JustMoved(); }
		bool HasItMoved(const std::string& loc) { return pieces[loc]->HasMoved(); }
		bool FirstMove(const std::string& loc) { return pieces[loc] != BLANK && pieces[loc]->FirstMove(); }
		std::string LastMovedLoc() { return last_moved; }

		/* captured pieces interface */
		std::vector<char> CapturedBy(char player);
		bool Captured() { return captured; }
		void Capture(const std::string& loc);
		void Recapture(const std::string& loc);

		bool in_bound(const std::string& loc) {
			return LEFT_COL <= loc[0] && loc[0] <= RIGHT_COL && BOT_ROW <= loc[1] && loc[1] <= TOP_ROW;
		}

		// Board() { Reset(); }

		bool Check();
		bool CheckMate();

		int Distance(const std::string& from, const std::string& to)  {
			return std::abs(from[0] - to[0]) + std::abs(from[1] - to[1]);
		}
};

#endif