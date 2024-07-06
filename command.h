#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
	public:
		virtual ~Command() {}
		virtual bool Execute() = 0; // return 1 if execution is successful
		virtual void Undo() = 0; // any valid execution can be undone
};

// int Distance(const std::string& from, const std::string& to)  {
// 	return std::abs(from[0] - to[0]) + std::abs(from[1] - to[1]);
// }

#endif