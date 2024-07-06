#ifndef PARSER_H
#define PARSER_H

#include "command.h"
#include <memory>

class Parser {
	public:
		Parser() {}
		std::unique_ptr<Command> ParseCommand(); // return a unique_ptr<Command> from text input
};

#endif