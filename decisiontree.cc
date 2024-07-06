#include "decisiontree.h"

DecisionTree* DecisionTree::AddDecision(std::unique_ptr<Command> decision) {
	DecisionTree* new_decision = new DecisionTree{this};
	new_decision->decision = std::move(decision);
	next_decisions.push_back(new_decision);
	return new_decision;
}

DecisionTree::~DecisionTree() {
	for (auto next : next_decisions) {
		delete next;
	}
}