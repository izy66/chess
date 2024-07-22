#ifndef BOARD_H
#define BOARD_H

#include "exceptions.h"
#include "moves/move.h"
#include "pieces/blank.h"
#include "pieces/piece.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "subject.h"
#include <vector>
#include <memory>
#include <map>
#include <stack>
#include <sstream>
#include <algorithm>
#include <random>

#define BLANK nullptr
#define FOG '?'
#define DRAW 'D'

class AbstractMove;
class Player;

class Board : public Subject {
	
	Blank blank;
	
	std::map<char, std::vector<char>> captured_by;
	
	std::stack<std::string> move_path;
	std::stack<std::string> move_origin;

	std::map<char, std::string> king_loc;
	std::stack<std::unique_ptr<AbstractMove>> moves;

	char player = WHITE, opponent = BLACK;
	bool game_over = false, draw = false;

	std::map<char, std::shared_ptr<Player>> players;
	std::map<char, float> scores;

	std::random_device rd;
	std::default_random_engine gen;

	protected:

		std::map<std::string, std::unique_ptr<Piece>> pieces;
	
		/* internal state refresher */
		void refresh_vision();

	public:

		Board() { gen = std::default_random_engine(rd()); }

		/* general interface */
		bool Empty(const std::string& loc) { return pieces[loc] == BLANK; }
		void SetPiece(const std::string&, char name, char player);
		void RemovePiece(const std::string&);
		char GetPieceName(const std::string&);
		virtual char PrintPieceName(const std::string&);  // overwritten in Fog of War
		char GetPiecePlayer(const std::string&);

		void PlayerMovesNext(char);

		virtual void Reset(); // overwritten in Horde, 960
		void Clear();
		void Print();

		bool LastMoved(const std::string&);

		std::vector<Piece*> GetHand(char player);
		void Place(std::unique_ptr<Piece>);
		std::unique_ptr<Piece> Retrieve(const std::string&);

		std::unique_ptr<Piece>& operator[](const std::string& loc) { return pieces[loc]; }

		/* game control interface */
		bool GameOver() const { return game_over; }
		void SetUpDone();

		void PlayerExit() { game_over = 1; }

		void AddHumanPlayer(char);
		void AddComputerPlayer(char, int level = 1);
		void PlayerMakeMove();

		void PlayerResign() {
			++scores[opponent];
			game_over = true;
		}

		void Draw() {
			scores[player] += 0.5;
			scores[opponent] += 0.5;
			draw = true;
			game_over = true;
		}

		void DisplayScores();
		

		/* action interface */
		void MakeMove(std::unique_ptr<AbstractMove>);
		void ApplyMove(std::unique_ptr<AbstractMove>);
		void MovePiece(const std::string&, const std::string&) noexcept;
		void UndoMove(const std::string&, const std::string&) noexcept;

		bool IsRevealingKing(Piece*, const std::string&);
		bool HaveAdvantage(const std::string&, char);

		std::string FindSafePlace(const std::unique_ptr<Piece>&);

		void Undo();

		void KingIsHere(const std::string&);

		/* game logic interface */
		std::string LastMove() { return move_path.top(); }
		

		/* captured pieces interface */
		std::vector<char> CapturedBy(char);
		bool CanBeCaptured(const std::string&, char);
		bool CanBeSeen(const std::string&, char);

		void Capture(char, char);
		void Release(char);

		bool InBound(const std::string& loc) {
			return LEFT_COL <= loc[0] && loc[0] <= RIGHT_COL && BOT_ROW <= loc[1] && loc[1] <= TOP_ROW;
		}

		bool Check(); // is my last move a check move?
		bool Checked(); // if the current player is getting checked
		bool CheckMate(); // is my last move a checkmate?
		bool StaleMate(); // is my last move a stalemate?

		int Distance(const std::string& from, const std::string& to)  {
			return std::abs(from[0] - to[0]) + std::abs(from[1] - to[1]);
		}

		/* for advanced ai */
		static const int STALE_SCORE = 10;
		static const int CHECK_SCORE = 20;
		static const int MAX_SCORE = 100000;
		int BoardScore();
};

#endif