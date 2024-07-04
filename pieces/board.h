#ifndef BOARD_H
#define BOARD_H
#include <string>

const char LEFT_COL = 'a';
const char RIGHT_COL = 'h';
const char TOP_ROW = '8';
const char BOT_ROW = '1';

#define BLACK 'B'
#define WHITE 'W'

class Board {
	// protected:
	// 	std::string loc;
	public: 
		// Board(const std::string& loc) : loc{loc} {}
		virtual ~Board() {}
		virtual char Print(const std::string& loc) = 0;
};

#endif