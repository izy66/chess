#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include "command.h"
#include <memory>
#include <vector>

class DecisionTree {
	std::unique_ptr<Command> decision;
	DecisionTree* last_decision;
	std::vector<DecisionTree*> next_decisions;

	public:
		DecisionTree(DecisionTree* last) : last_decision{last} {}
		DecisionTree* AddDecision(std::unique_ptr<Command> decision);
		DecisionTree* Backtrace() { return last_decision; }
		~DecisionTree();
};

#endif 