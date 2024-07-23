#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square {
	public:
		virtual ~Square() {}
		virtual char Print(const std::string& loc) const = 0;
		virtual char Print() const = 0;
		virtual bool Empty() const = 0;
};

#endif