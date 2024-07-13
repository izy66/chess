#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "parser.h"
#include "chessboard.h"
#include "decisiontree.h"
#include <memory>
#include <iostream>
#include <stack>

class Controller {
	ChessBoard* chess_board;

	std::shared_ptr<DecisionTree> decisions; // Controller owns the decision tree
	std::shared_ptr<DecisionTree> recent_decision;
	
	std::unique_ptr<Parser> parser;

	float white_score, black_score;
	
	public:
		Controller(ChessBoard* board) : chess_board{board}, decisions{std::make_shared<DecisionTree>()}, recent_decision{decisions}, parser{std::make_unique<Parser>()}, white_score{0}, black_score{0} {}
		~Controller();

		void StartGame(); // start game flow
		bool RunGame(); // run a match until ctrl + D
		void Setup(); // setup mode

		void WhiteWon() { 
			std::cout << "White won!" << std::endl;
			++white_score; 
		}
		void BlackWon() { 
			std::cout << "Black won!" << std::endl;
			++black_score; 
		}
		void Draw() { white_score += 0.5; black_score += 0.5; }

		void DisplayScores();
		void DisplayFinalScores();

		void GameOver();
};

#endif