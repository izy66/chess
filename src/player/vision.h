#ifndef VISION_H
#define VISION_H

#include <string>
#include <map>
#include <memory>

class Board;
class Player;
class Piece;

class Vision {
	Board* chess_board;
	std::map<std::string, int> vision;
	public:
		Vision(Board*);
		void Refresh(std::vector<std::shared_ptr<Piece>>);
		int CanSee(const std::string&);
};

#endif