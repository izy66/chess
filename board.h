#ifndef BOARD_H
#define BOARD_H

#include "pieces/blank.h"
#include "pieces/piece.h"
#include <vector>
#include <memory>
#include <map>
#include <stack>

#define BLANK nullptr
#define FOG '?'

class Board {
	std::map<std::string, std::unique_ptr<Piece>> pieces;
	std::stack<std::unique_ptr<Piece>> captured_pieces;
	std::vector<char> captured_white, captured_black;
	Blank blank;
	std::map<char, std::map<std::string, int>> visibility_counter;

	char player = WHITE, opponent = BLACK;
	std::map<char, std::string> king_loc;
	bool game_over = false;

	public:
		bool empty(const std::string& loc) { return pieces[loc] == BLANK; }
		bool set(const std::string& loc, char name, char col);
		char get_name(const std::string& loc);
		char get_player(const std::string& loc);
		
		bool remove(const std::string& loc);

		void refresh_vision();

		bool checked();
		bool check_mated();

		void clear();
		void reset();

		bool move_piece(const std::string& from, const std::string& to);
		void just_moved(const std::string& loc) { pieces[loc]->JustMoved(); }
		bool has_moved(const std::string& loc) { return pieces[loc]->HasMoved(); }
		bool first_move(const std::string& loc) { return pieces[loc] != BLANK && pieces[loc]->FirstMove(); }

		void capture(const std::string& loc);
		void recapture(const std::string& loc);

		std::vector<char> captured_color(char color);

		bool in_bound(const std::string& loc) {
			return LEFT_COL <= loc[0] && loc[0] <= RIGHT_COL && BOT_ROW <= loc[1] && loc[1] <= TOP_ROW;
		}

		Board() { reset(); }
};

#endif