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

#define BLANK nullptr
#define FOG '?'
#define DRAW 'D'

class AbstractMove;
class Player;

class Board : public Subject {
	
	Blank blank;
	
	std::map<char, std::vector<char>> captured_by;
	
	std::stack<std::string> move_path;

	std::map<char, std::string> king_loc;
	std::stack<std::unique_ptr<AbstractMove>> moves;

	std::stack<std::shared_ptr<Piece>> promoted;

	char player = WHITE, opponent = BLACK;
	bool game_over = false, draw = false;

	std::map<char, std::shared_ptr<Player>> players;
	std::map<char, float> scores;


	static const int NUM_PIECE = 6;
	const char piece_rank[NUM_PIECE] = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
	int get_rank(char c) const { 
		for (int i = 0; i < 6; ++i) if (piece_rank[i] == c) return i; 
		return -1;
	}

	protected:
	
		std::map<std::string, std::shared_ptr<Piece>> pieces;
	
		/* internal state refresher */
		void refresh_vision();

	public:
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

		std::shared_ptr<Piece>& operator[](const std::string& loc) { return pieces[loc]; }

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
		void MakeMove(std::unique_ptr<AbstractMove> move);
		void MovePiece(const std::string& , const std::string&) noexcept;
		void UndoMove(const std::string& , const std::string&) noexcept;
		bool CanMove(const std::string&);
		std::string TryCheckMove(const std::shared_ptr<Piece>&);
		std::string TryCheckMate(const std::shared_ptr<Piece>&);
		std::string TryStaleMate(const std::shared_ptr<Piece>&);
		bool IsCheckMove(const std::shared_ptr<Piece>&, const std::string&);
		bool IsCheckMate(const std::shared_ptr<Piece>&, const std::string&);
		bool IsStaleMate(const std::shared_ptr<Piece>&, const std::string&);
		bool IsRevealingKing(Piece*, const std::string&);

		void Undo();

		void KingIsHere(const std::string&);

		/* game logic interface */
		std::string LastMove() { return move_path.top(); }
		virtual bool CanPromote(const std::string&);
		std::shared_ptr<Piece> Promote(const std::string&, char);
		void Demote(std::shared_ptr<Piece>&);

		/* captured pieces interface */
		std::vector<char> CapturedBy(char);
		std::shared_ptr<Piece> Capture(const std::string&);
		void Release(std::shared_ptr<Piece>&);
		bool CanBeCaptured(const std::string&, char);
		bool CanBeSeen(const std::string&, char);
		std::string BestCaptureMove(const std::shared_ptr<Piece>&);

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
};

#endif