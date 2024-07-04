#ifndef BLANK_H
#define BLANK_H

#include "piece.h"

class Blank : public Board {
	public: 
		// Blank(const std::string& loc) : loc{loc} {}
		~Blank() {}
		char Print(const std::string& loc) override;
};

#endif