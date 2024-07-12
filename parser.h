#ifndef PARSER_H
#define PARSER_H

#include "moves/move.h"
#include "chessboard.h"
#include <memory>

class Parser {
	public:
		Parser() {}
		std::unique_ptr<Move> ParseCommand(ChessBoard*, std::string&, std::string&);
};

#endif