#ifndef BOARD_H
#define BOARD_H

#include "pieces/blank.h"
#include "pieces/piece.h"
#include "subject.h"
#include "player/player.h"
#include "player/human.h"
#include "player/random_player.h"
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
		bool game_over = false, captured = false, draw = false;
		std::string last_moved;

		std::vector<std::unique_ptr<Player>> players;
		size_t cur_player = 0;

		/* internal state refreshers */
		void refresh_vision();

	public:
		/* general interface */
		bool Empty(const std::string& loc) { return pieces[loc] == BLANK; }
		bool SetPiece(const std::string& loc, char name, char player);
		bool RemovePiece(const std::string& loc);
		virtual char GetPieceName(const std::string& loc); // overwritten in Fog of War
		char GetPiecePlayer(const std::string& loc);
		char CurrentPlayer() const { return player; }
		char WhoWon() const { return who_won; }

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
		bool Drawed() { return draw; }
		bool SetUpDone() { 
			if (king_loc[player] != "" && king_loc[opponent] != "") return 1;
			if (king_loc[WHITE] == "") {
				std::cout << "You need a white king on board!" << std::endl;
			}
			if (king_loc[BLACK] == "") {
				std::cout << "You need a black king on board!" << std::endl;
			}
			return 0;
		}

		void AddHumanPlayer(char team);
		void AddComputerPlayer(char team, int level = 1);
		bool PlayerMakeMove() { 
			if (player == WHITE) {
				std::cout << "White to move." << std::endl;
			} else {
				std::cout << "Black to move." << std::endl;
			}
			if (!players[cur_player]->MakeMove()) return 0;
			cur_player = (cur_player + 1) % players.size();
			return 1;
		}

		bool PlayerResign() {
			who_won = opponent;
			return 1;
		}

		bool Draw() {
			draw = true;
			return 1;
		}

		/* action interface */
		bool ValidMove(const std::string& from, const std::string& to);
		bool MakeMove(std::unique_ptr<Move>& move);
		bool MovePiece(const std::string& from, const std::string& to);
		bool CanMove(const std::string&);
		std::string MakeRandomMove(const std::string&);
		void JustMoved(const std::string& loc) { pieces[loc]->JustMoved(); }
		bool HasItMoved(const std::string& loc) { return pieces[loc]->HasMoved(); }
		bool FirstMove(const std::string& loc) { return pieces[loc] != BLANK && pieces[loc]->FirstMove(); }
		std::string LastMovedLoc() { return last_moved; }
		bool Undo() { return players[cur_player]->Undo(); }

		/* game logic interface */
		virtual bool IsEnPassant(const std::string& from, const std::string& to);
		virtual bool IsCastling(const std::string& from, const std::string& to);
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

		bool Check(); // is my last move a check move?
		bool Checked(); // if the current player is getting checked
		bool CheckMate(); // is my last move a checkmate?
		bool StaleMate(); // is my last move a stalemate?

		int Distance(const std::string& from, const std::string& to)  {
			return std::abs(from[0] - to[0]) + std::abs(from[1] - to[1]);
		}
};

#endif