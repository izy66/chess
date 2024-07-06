#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "parser.h"
#include "chessboard.h"
#include "decisiontree.h"
#include <memory>
#include <iostream>

class Controller {
	ChessBoard* chess_board;

	DecisionTree* decisions; // Controller owns the decision tree
	DecisionTree* recent_decision;
	
	std::unique_ptr<Parser> parser;

	char player, opponent;

	int white_score, black_score;
	
	public:
		Controller(ChessBoard* board) : chess_board{board}, decisions{new DecisionTree(nullptr)}, recent_decision{decisions}, parser{std::make_unique<Parser>()}, player{WHITE}, opponent{BLACK}, white_score{0}, black_score{0} {}
		~Controller();

		void StartGame(); // plays matches (not in setup mode)
		bool RunGame(); // run a match
		
		void FetchMove(); // input -> command -> execute -> record

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

		void WhiteMovesNext() { player = WHITE; opponent = BLACK; }
		void BlackMovesNext() { player = BLACK; opponent = WHITE; }

		void DisplayScores();
		void DisplayFinalScores();

		void GameOver();
};

#endif