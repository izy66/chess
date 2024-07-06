#ifndef BLANK_H
#define BLANK_H

#include "square.h"

class Blank : public Square {
	public: 
		~Blank() {}
		char Print(const std::string& loc) const override;
		bool Empty() const override { return 1; }
};

#endif