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
#define DRAW 'D'

class Move;

class Board : public Subject {
	protected:
		std::map<std::string, std::unique_ptr<Piece>> pieces;
		std::stack<std::unique_ptr<Piece>> captured_pieces;
		std::map<char, std::vector<char>> captured_by;
		Blank blank;
		std::map<char, std::map<std::string, int>> visibility_counter;

		char player = WHITE, opponent = BLACK, who_won;
		std::map<char, std::string> king_loc;
		bool game_over = false, captured = false;
		std::string last_moved;

		/* internal state refreshers */
		void refresh_vision();

	public:
		/* general interface */
		bool Empty(const std::string& loc) { return pieces[loc] == BLANK; }
		bool SetPiece(const std::string& loc, char name, char player);
		bool RemovePiece(const std::string& loc);
		virtual char GetPieceName(const std::string& loc); // overwritten in Fog of War
		char GetPiecePlayer(const std::string& loc);
		char Player() { return player; }
		char WhoWon() { return who_won; }

		void PlayerMovesNext(char next_player) {
			if (next_player == WHITE) { player = WHITE; opponent = BLACK; }
			else { player = BLACK; opponent = WHITE; }
		}

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

		virtual bool IsEnPassant(const std::string& from, const std::string& to);
		virtual bool IsCastling(const std::string& from, const std::string& to); // given some arbitrary move, is it castling?
		virtual bool CanPromote(const std::string& from);

		bool IsKing(const std::string& loc) { return toupper(pieces[loc]->Name()) == KING; }
		bool IsKing(const std::unique_ptr<Piece>& piece) { return toupper(piece->Name()) == KING; }
		bool IsPawn(const std::string& loc) { return toupper(pieces[loc]->Name()) == PAWN; }

		/* captured pieces interface */
		std::vector<char> CapturedBy(char player);
		bool IsCaptureMove(const std::string& from, const std::string& to);
		bool Captured() { return captured; }
		void Capture(const std::string& loc);
		void Recapture(const std::string& loc);
		bool CanBeCapturedBy(char player, const std::string& loc) { return visibility_counter[player][loc] > 0; }

		bool in_bound(const std::string& loc) {
			return LEFT_COL <= loc[0] && loc[0] <= RIGHT_COL && BOT_ROW <= loc[1] && loc[1] <= TOP_ROW;
		}

		// Board() { Reset(); }

		bool Check(); // is my last move a check move
		bool Checked(); // if the current player is getting checked
		bool CheckMate(); // is my last move a checkmate?
		bool StaleMate(); // is my last move a stalemate?

		int Distance(const std::string& from, const std::string& to)  {
			return std::abs(from[0] - to[0]) + std::abs(from[1] - to[1]);
		}
};

#endif