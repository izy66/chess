#ifndef BOARD_H
#define BOARD_H

#include "pieces/square.h"
#include "pieces/piece.h"
#include <memory>
#include <map>
#include <vector>

class Board {
	std::map<std::string, std::unique_ptr<Square>> pieces;
	std::vector<char> captured_pieces;

	public:
		bool set(const std::string& loc, char name, char col);
		char get(const std::string& loc) { return pieces[loc]->Print(loc); }
		char get_color(const std::string& loc) {
			if (pieces[loc]->Empty()) return pieces[loc]->Print(loc);
			return isupper(pieces[loc]->Print(loc)) ? WHITE : BLACK;
		}
		
		void clear();
		bool remove(const std::string& loc);
		void reset();

		bool empty(const std::string& loc) { return pieces[loc]->Empty(); }

		void capture(const std::string& loc) {
			if (!pieces[loc]->Empty()) {
				captured_pieces.push_back(pieces[loc]->Print(loc));
			}
		}

		std::vector<char> captured_color(char color);

		Board() { reset(); }
};

#endif