#ifndef VISION_H
#define VISION_H

#include <string>
#include <map>
#include <memory>

class Board;
class Player;

class Vision {
	Board* chess_board;
	Player* player;
	std::map<std::string, int> vision;
	public:
		Vision(Board*, Player*);
		void Refresh();
		int CanSee(const std::string&);
};

#endif