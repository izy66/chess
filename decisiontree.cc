#include "decisiontree.h"

DecisionTree* DecisionTree::AddDecision(Move* decision) {
	DecisionTree* new_decision = new DecisionTree{this};
	new_decision->decision = decision;
	next_decisions.push_back(new_decision);
	return new_decision;
}

DecisionTree::~DecisionTree() {
	for (auto next : next_decisions) {
		delete next;
	}
}

DecisionTree* DecisionTree::UndoDecision(ChessBoard* chess_board) {
	decision->Undo(chess_board);
	return last_decision; 
}