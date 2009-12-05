/**
 * @file Chain.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <iostream>
#include "assert.h"

//FireSim
#include "Chain.h"

Chain::Chain(std::string name, bool finalChain, bool usedChain) :
	_name(name), _policy(""), _rules(), _finalChain(finalChain), _usedChain(usedChain) {
}

Chain::Chain(std::string name, std::string policy, bool finalChain, bool usedChain) :
	_name(name), _policy(policy), _rules(), _finalChain(finalChain), _usedChain(usedChain) {
}

Chain::~Chain() {
	for(std::vector<Rule*>::iterator it = _rules.begin(); it != _rules.end(); it++) {
		delete *it;
	}
}

std::string Chain::getName(){
	return _name;
}

bool Chain::isFinal(){
	return _finalChain;
}

void Chain::setUsed() {
	_usedChain = true;
}

void Chain::add(Rule* rule){
	_rules.push_back(rule);
}

void Chain::printClickClassifiers(std::ostream& ostream, std::string prefix){
	for (int index = 0; index < _rules.size(); index++) {
		ostream << "Idle -> ";
		if (!_rules[index]->hasCondition() || _rules[index]->ignore()){
			ostream << prefix << this->getName() << (index + 1) << " :: IPClassifier(-);" << std::endl;
		} else if (_rules[index]->needsIPClassifier() && _rules[index]->needsClassifier()) {
			ostream << prefix << this->getName() << (index + 1) << " :: IPClassifier(";
			_rules[index]->printClickIPClassifier(ostream);
			ostream << "-);" << std::endl;
			ostream << "Idle -> ";
			ostream  << prefix << this->getName() << (index + 1) << "B :: Classifier(";
			_rules[index]->printClickClassifier(ostream);
			ostream << "-);" << std::endl;
		} else if (_rules[index]->needsIPClassifier()) {
			//only ipclassifier is needed
			ostream << prefix << this->getName() << (index + 1) << " :: IPClassifier(";
			_rules[index]->printClickIPClassifier(ostream);
			ostream << "-);" << std::endl;
		} else if (_rules[index]->needsClassifier()){
			//only classifier is needed
			ostream  << prefix << this->getName() << (index + 1) << " :: Classifier(";
			_rules[index]->printClickClassifier(ostream);
			ostream << "-);" << std::endl;
		} else {
			assert(false);
		}

	}
	if((_rules.empty() && _usedChain) || (!_rules.empty())) {
		ostream << "Idle -> " << prefix << this->getName() << (_rules.size() + 1) << " :: IPClassifier(-);" << std::endl;
	}
}

void Chain::printClickTraceSimulation(std::ostream& ostream, std::string prefix, std::string postfix){
	int nrOfRules = _rules.size();
	for (int index = 0; index < (nrOfRules-1); index++) {
		Chain* target = _rules[index]->getJumpChain();
		if (_rules[index]->ignore()) {
			//this rule must be ignored ==> jump to next rule
			ostream << prefix << this->getName() << (index + 1) << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (index + 1) << postfix << ")"
					<< " -> " << prefix << this->getName() << (index + 2) << postfix << ";" << std::endl;
		} else if (!_rules[index]->hasCondition()){
			//this rule has no conditions ==> jump to target
			ostream << prefix << this->getName() << (index + 1) << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (index + 1) << postfix << ")";
			if (target->getName() == "RETURN") {
				ostream << " -> bt;" << std::endl;
			} else if (target->getName() == "MASQUERADE") {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (index + 2) << postfix << ")"
						<< " -> masq;" << std::endl;
			} else if ((target->getName() == "SNAT") || (target->getName() == "DNAT")) {
				_rules[index]->printIPRewriter(ostream);
				ostream	<< " -> " << prefix << this->getName() << (index + 2) << postfix << ";" <<std::endl;
			} else if (target->isFinal()) {
				ostream << " -> " << target->getName() << ";" <<std::endl;
			} else {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (index + 2) << postfix << ")"
						<< " -> " << prefix << target->getName() << "1" << postfix << ";" << std::endl;
			}
		} else if (_rules[index]->needsIPClassifier() && _rules[index]->needsClassifier()) {
			//this rule has conditions that must be simulated by an IPClassifier and a general Classifier
			ostream << prefix << this->getName() << (index + 1) << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (index + 1) << postfix << ")"
					<< " -> " << prefix << this->getName() << (index + 1) << "B;" << std::endl;

			ostream << prefix << this->getName() << (index + 1) << "[1]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (index + 1) << postfix << ")"
					<< " -> " << prefix << this->getName() << (index + 2) << postfix << ";" << std::endl;

			ostream << prefix << this->getName() << (index + 1) << "B[0]";
			if (target->getName() == "RETURN") {
				ostream << " -> bt;" << std::endl;
			} else if (target->getName() == "MASQUERADE") {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (index + 2) << postfix << ")"
						<< " -> masq;" << std::endl;
			} else if ((target->getName() == "SNAT") || (target->getName() == "DNAT")) {
				_rules[index]->printIPRewriter(ostream);
				ostream	<< " -> " << prefix << this->getName() << (index + 2) << postfix << ";" <<std::endl;
			} else if (target->isFinal()) {
				ostream << " -> " << target->getName() << ";" <<std::endl;
			} else {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (index + 2) << postfix << ")"
						<< " -> " << prefix << target->getName() << "1" << postfix << ";" <<std::endl;
			}
			ostream << prefix << this->getName() << (index + 1) << "B[1]"
					<< " -> " << prefix << this->getName() << (index + 2) << postfix << ";" << std::endl;
		} else if (_rules[index]->needsIPClassifier() || _rules[index]->needsClassifier()) {
			//only 1 classifier is needed
			ostream << prefix << this->getName() << (index + 1) << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (index + 1) << postfix << ")";
			if (target->getName() == "RETURN") {
				 ostream << " -> bt;" << std::endl;
			} else if (target->getName() == "MASQUERADE") {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (index + 2) << postfix << ")"
						<< " -> masq;" << std::endl;
			} else if ((target->getName() == "SNAT") || (target->getName() == "DNAT")) {
				 _rules[index]->printIPRewriter(ostream);
				ostream	<< " -> " << prefix << this->getName() << (index + 2) << postfix << ";" <<std::endl;
			} else if (target->isFinal()) {
				ostream << " -> " << target->getName() << ";" <<std::endl;
			} else {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (index + 2) << postfix << ")"
						<< " -> " << prefix << target->getName() << "1" << postfix << ";" << std::endl;
			}
			ostream << prefix << this->getName() << (index + 1) << "[1]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (index + 1) << postfix << ")"
					<< " -> " << prefix << this->getName() << (index + 2)  << postfix << ";" << std::endl;
		} else {
			assert(false);
		}
	}

	if (nrOfRules == 0 && _usedChain) {
		if (_policy=="") {
			//no policy set ==> backtrace
			ostream << prefix << this->getName() << "1[0] -> bt;" << std::endl;
		} else {
			//jump to policy
			ostream << prefix << this->getName() << "1[0]"
					<< " ->  Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << "1" << postfix << ")"
					<< " -> " << _policy << "; //Default policy" << std::endl;
		}
	} else if(nrOfRules > 0) {
		//Process last rule
		Rule* rule = _rules[_rules.size()-1];
		Chain* target = rule->getJumpChain();

		if (rule->ignore()) {
			ostream << prefix << this->getName() << _rules.size() << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << ")"
					<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" << std::endl;
			if (_policy==""){
				//no policy set ==> backtracking needed
				ostream << prefix << this->getName() << (_rules.size() + 1) << "[0] -> bt;" << std::endl;
			} else {
				//jump to default policy
				ostream << prefix << this->getName() << (_rules.size()) << "[0]"
						<< " -> " << prefix << this->getName() << postfix << (_rules.size() + 1) << ";" << std::endl;
				ostream << prefix << this->getName() << (_rules.size() + 1) << "[0]"
						<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")"
						<< " -> " << _policy << "; //Default policy" << std::endl;
			}
		} else if (!rule->hasCondition()){
			//this rule has no conditions ==> jump to target
			ostream << prefix << this->getName() << _rules.size() << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << ")";
			if (target->getName() == "RETURN") {
				ostream << " -> bt;" << std::endl;
			} else if (target->getName() == "MASQUERADE") {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")"
						<< " -> masq;" << std::endl;
			} else if ((target->getName() == "SNAT") || (target->getName() == "DNAT")) {
				rule->printIPRewriter(ostream);
				ostream	<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" <<std::endl;
			} else if (target->isFinal()) {
				ostream << " -> " << target->getName() << ";" <<std::endl;
			} else {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")"
						<< " -> " << prefix << target->getName() << "1" << postfix << ";" << std::endl;
			}
			if (_policy=="") {
				//no policy set ==> backtrace
				ostream << prefix << this->getName() << (_rules.size() + 1) << "[0] -> bt;" << std::endl;
			} else {
				//jump to policy
				ostream << prefix << this->getName() << (_rules.size() + 1) << "[0]"
						<< " ->  Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")"
						<< " -> " << _policy << "; //Default policy" << std::endl;
			}
		} else if (rule->needsIPClassifier() && rule->needsClassifier()) {
			ostream << prefix << this->getName() << _rules.size() << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << ")"
					<< " -> " << prefix << this->getName() << _rules.size() << "B;" << std::endl;
			ostream << prefix << this->getName() << (_rules.size()) << "[1]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << ")"
					<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" << std::endl;
			ostream << prefix << this->getName() << _rules.size() << "B[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << postfix << ")";
			if (target->getName() == "RETURN") {
				ostream << " -> bt;" << std::endl;
			} else if (target->getName() == "MASQUERADE") {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")"
						<< " -> masq;" << std::endl;
			} else if ((target->getName() == "SNAT") || (target->getName() == "DNAT")) {
				rule->printIPRewriter(ostream);
				ostream	<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" <<std::endl;
			} else if (target->isFinal()){
				ostream << " -> " << target->getName() << ";" <<std::endl;
			} else {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << ( _rules.size() + 1) << postfix << ")"
						<< " -> " << prefix << target->getName() << "1" << postfix << ";" << std::endl;
			}
			ostream << prefix << this->getName() << (_rules.size()) << "B[1]"
					<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" << std::endl;
			ostream << prefix << this->getName() << (_rules.size() + 1) << "[0]"
					<< " ->  Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")";
			if(_policy=="") {
				//perform backtracking because no default policy is set
				ostream << " -> bt;" << std::endl;
			} else {
				//jump to default policy
				ostream << " -> " << _policy << "; //Default policy" << std::endl;
			}
		} else if (rule->needsIPClassifier() || rule->needsClassifier()) {
			ostream << prefix << this->getName() << _rules.size() << "[0]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << ")";
			if (target->getName() == "RETURN") {
				ostream << " -> bt;" << std::endl;
			} else if (target->getName() == "MASQUERADE") {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")"
						<< " -> masq;" << std::endl;
			} else if ((target->getName() == "SNAT") || (target->getName() == "DNAT")) {
				rule->printIPRewriter(ostream);
				ostream	<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" <<std::endl;
			} else if (target->isFinal()){
				ostream << " -> " << target->getName() << ";" <<std::endl;
			} else {
				ostream << " -> Script(TYPE PACKET, write bt.trace " << prefix << this->getName() << ( _rules.size() + 1) << postfix << ")"
						<< " -> " << prefix << target->getName() << "1" << postfix << ";" <<std::endl;
			}
			ostream << prefix << this->getName() << (_rules.size()) << "[1]"
					<< " -> Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << _rules.size() << postfix << ")"
					<< " -> " << prefix << this->getName() << (_rules.size() + 1) << postfix << ";" << std::endl;
			ostream << prefix << this->getName() << (_rules.size() + 1) << "[0] "
					<< " ->  Script(TYPE PACKET, write ACCEPT.from " << prefix << this->getName() << (_rules.size() + 1) << postfix << ")";
			if (_policy=="") {
				ostream << " -> bt;" << std::endl;
			} else {
				ostream << " -> " << _policy << "; //Default policy" << std::endl;
			}
		} else {
			assert(false);
		}
	}
}

void Chain::printPrettyPrinters(std::ostream& ostream, std::string prefix){
	for (int index = 0; index < _rules.size(); index++) {
		ostream << "Idle -> ";
		if (_rules[index]->ignore()){
			ostream << prefix << this->getName() << (index + 1) << "Print :: Script(TYPE PACKET, print \"*** Rule ignored: "<< _rules[index]->getIpTablesText().substr(3, std::string::npos) <<" ***\") -> " << prefix << this->getName() << (index + 1) << ";" << std::endl;
		} else {
			ostream << prefix << this->getName() << (index + 1) << "Print :: Script(TYPE PACKET, print \""<< _rules[index]->getIpTablesText().substr(3, std::string::npos) <<"\") -> " << prefix << this->getName() << (index + 1) << ";" << std::endl;
		}
	}
	if((_rules.empty() && _usedChain) || (!_rules.empty())) {
		if(_policy != "") {
			ostream << "Idle -> " << prefix << this->getName() <<  (_rules.size() + 1) << "Print :: Script(TYPE PACKET, print \"*** Policy of " << this->getName() << " chain triggered: " << _policy << " ***\")"
					<< " -> " << prefix << this->getName() << (_rules.size() + 1) << ";" << std::endl;
		} else {
			ostream << "Idle -> " << prefix << this->getName() << (_rules.size() + 1) << "Print :: Script(TYPE PACKET, print \"*** Backtracking: leaving " << this->getName() << " chain ***\")"
					<< " -> " << prefix << this->getName() << (_rules.size() + 1) << ";" << std::endl;
		}
	}
}
