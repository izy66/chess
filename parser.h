#ifndef PARSER_H
#define PARSER_H

#include "move.h"
#include "chessboard.h"
#include <memory>

class Parser {
	public:
		Parser() {}
		Move* ParseCommand(ChessBoard*, std::string&, std::string&);
};

#endif