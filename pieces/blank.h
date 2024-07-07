#ifndef BLANK_H
#define BLANK_H

#include "square.h"

#define LIGHT '+'
#define DARK '-'

class Blank {
	public: 
		~Blank() {}
		char Print(const std::string& loc) const;
		bool Empty() const { return 1; }
};

#endif