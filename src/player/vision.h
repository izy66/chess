#ifndef VISION_H
#define VISION_H

#include <string>
#include <map>
#include <memory>
#include <vector>

class Board;
class Player;
class Piece;

class Vision {
	std::map<std::string, int> vision;
	public:
		// Vision::Vision(Board* chess_board) : chess_board{chess_board} {}
		void Refresh(std::vector<std::shared_ptr<Piece>>);
		int CanSee(const std::string&);
};

#endif