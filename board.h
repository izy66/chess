#ifndef BOARD_H
#define BOARD_H

#include "pieces/blank.h"
#include "pieces/piece.h"
#include <vector>
#include <memory>
#include <map>
#include <stack>

#define BLANK nullptr

class Board {
	std::map<std::string, std::unique_ptr<Piece>> pieces;
	std::stack<std::unique_ptr<Piece>> captured_pieces;
	std::vector<char> captured_white, captured_black;
	Blank blank;

	public:
		bool empty(const std::string& loc) { return pieces[loc] == BLANK; }
		bool set(const std::string& loc, char name, char col);
		char get(const std::string& loc);
		char color(const std::string& loc);
		
		bool remove(const std::string& loc);

		void clear();
		void reset();

		void move_piece(const std::string& from, const std::string& to);
		void just_moved(const std::string& loc) { pieces[loc]->JustMoved(); }
		bool has_moved(const std::string& loc) { return pieces[loc]->HasMoved(); }
		bool first_move(const std::string& loc) { return pieces[loc] != BLANK && pieces[loc]->FirstMove(); }

		void capture(const std::string& loc);
		void recapture(const std::string& loc);

		std::vector<char> captured_color(char color);

		Board() { reset(); }
};

#endif