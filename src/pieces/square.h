#ifndef SQUARE_H
#define SQUARE_H

#include <string>

#define LEFT_COL 	'a'
#define RIGHT_COL 'h'
#define TOP_ROW 	'8'
#define BOT_ROW 	'1'

class Square {
	public:
		virtual ~Square() {}
		virtual char Print(const std::string& loc) const = 0;
		virtual char Print() const = 0;
		virtual bool Empty() const = 0;
};

#endif