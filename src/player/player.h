#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <stack>
#include <sstream>
#include <memory>

class Board;
class Move;
class Parser;
class Piece;

class Player {
	protected:	
		char player;
		std::unique_ptr<Parser> parser;
		std::stack<std::unique_ptr<Move>> moves;
		std::vector<std::shared_ptr<Piece>> pieces;

		bool is_human, make_move;

		virtual bool take_action(Board*) = 0;

	public:
		Player(char);
		virtual ~Player();
		virtual bool MakeMove(Board*) = 0;
		virtual bool TakeAction(Board*);
		virtual bool Undo(Board*);
		bool IsHuman() { return is_human; }
};

#endif