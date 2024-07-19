#ifndef PARSER_H
#define PARSER_H

#include "board.h"
#include <memory>

class Move;

class Parser {
	public:
		std::unique_ptr<Move> ParseCommand(Board*, const std::string&, const std::string&, char promotion = PAWN) noexcept;
};

#endif