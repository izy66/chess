#include "blank.h"
#include <string>

#define LIGHT '@'
#define DARK '#'

char Blank::Print(const std::string& loc) const {
	int x = loc[0] - LEFT_COL;
	int y = TOP_ROW - loc[1];
	if ((x + y) % 2 == 0) return LIGHT;
	return DARK;
}