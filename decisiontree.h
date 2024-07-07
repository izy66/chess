#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include "move.h"
#include <memory>
#include <vector>

class ChessBoard;

class DecisionTree {
	Move* decision;
	DecisionTree* last_decision;
	std::vector<DecisionTree*> next_decisions;

	public:
		DecisionTree(DecisionTree* last) : last_decision{last} {}
		DecisionTree* AddDecision(Move* decision);
		DecisionTree* UndoDecision(ChessBoard*);
		~DecisionTree();
};

#endif 