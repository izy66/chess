#ifndef PARSER_H
#define PARSER_H

#include "board.h"
#include <memory>

class Move;

class Parser {
	public:
		std::unique_ptr<Move> ParseCommand(Board*, std::string&, std::string&, char promotion = PAWN);
};

#endif