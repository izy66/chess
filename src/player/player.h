#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <stack>
#include <sstream>
#include <memory>

class Board;
class Move;
class Parser;
class Piece;
class Vision;

class Player {

	protected:	
		Board* chess_board;
		char player;
		std::unique_ptr<Parser> parser;
		// std::map<std::string, std::shared_ptr<Piece>> hand;
		std::unique_ptr<Vision> vision;

		bool is_human;

		std::vector<std::shared_ptr<Piece>> get_hand() const;

	public:
		Player(Board*, char);
		virtual ~Player();
		// virtual void AddPiece(const std::shared_ptr<Piece>&);
		// void DiscardHand();
		virtual void TakeAction() = 0;
		virtual void MakeMove() = 0;

		void RefreshVision();
		int CanSee(const std::string&) const;
		bool CanCapture(const std::string&) const;

		// void DiscardPiece(const std::string&);

		// class Iterator {
		// 	friend class Player;
		// 	std::vector<std::shared_ptr<Piece>>::const_iterator iter;
		// 	public:
		// 		Iterator(auto iter) : iter{iter} {}
		// 		auto operator*() const { return *iter; }
		// 		auto operator++() { ++iter; }
		// 		auto operator!=(const Iterator& other) const { return iter != other.iter; }
		// };

		// Iterator begin() const { return Iterator{hand.begin()}; }
		// Iterator end() const { return Iterator{hand.end()}; }
};

#endif