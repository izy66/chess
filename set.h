#ifndef SET_H
#define SET_H
#include <memory>
#include <map>
#include "pieces/board.h"

class Set {
	std::map<std::string, std::unique_ptr<Board>> pieces;
	// std::map<std::string, Board*> pieces;
	public:
		void set(const std::string& loc, char name, char col);
		char get(const char c, const char r) { 
			const std::string loc = std::string() + c + r;
			return pieces[loc]->Print(loc); 
		}
		void clear();
		void remove(const std::string& loc);

		Set() { clear(); }
};

#endif 