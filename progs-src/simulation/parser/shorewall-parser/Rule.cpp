/**
 * @file Rule.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include "assert.h"
//Poco
//FireSim
#include "Rule.h"
#include "Chain.h"
#include "conditions/LowLevelCondition.h"
#include "conditions/IgnorableCondition.h"

Rule::Rule(std::string iptablesFormat, std::vector<Condition*> conditions,  Chain* target) :
	_iptablesFormat(iptablesFormat), _conditions(conditions), _target(target), _natIP("-"), _natPort("-") {
}

Rule::Rule(std::string iptablesFormat, std::vector<Condition*> conditions, Chain* target, std::string natIP, std::string natPort) :
	_iptablesFormat(iptablesFormat), _conditions(conditions), _target(target), _natIP(natIP), _natPort(natPort) {
}


Rule::~Rule() {
	for(std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end(); it++) {
		delete *it;
	}
}

Chain* Rule::getJumpChain(){
	return _target;
}

bool Rule::hasCondition(){
	return (!_conditions.empty());
}

bool Rule::ignore(){
	assert(_target!=0);
	if(_target->getName()=="ULOG"){
		//ignore logging system
		return true;
	}
	if (_conditions.empty()) {
		return false;
	}
	for(std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end(); it++) {
		if(!dynamic_cast<IgnorableCondition*>(*it)){
			//a not-ignorable condition found!
			return false;
		}
	}
	return true;
}

bool Rule::needsIPClassifier() {
	for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end(); it++) {
		if (!dynamic_cast<LowLevelCondition*>(*it)) {
			return true;
		}
	}
	return false;
}

bool Rule::needsClassifier() {
	for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end(); it++) {
		if (dynamic_cast<LowLevelCondition*>(*it)) {
			return true;
		}
	}
	return false;
}

void Rule::printClickIPClassifier(std::ostream& ostream){
		for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end(); it++) {
			if(!dynamic_cast<IgnorableCondition*>(*it) && !dynamic_cast<LowLevelCondition*>(*it)) {
				(*it)->print(ostream);
				if ((it+1) != _conditions.end()) {
					ostream << " ";
				}
			}
		}
		if(!this->ignore()){
			ostream << ", ";
		}
}

void Rule::printClickClassifier(std::ostream& ostream){
	bool firstOccurrence = true;
	for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end(); it++) {
		if (LowLevelCondition* cond = dynamic_cast<LowLevelCondition*>(*it)) {
			if(!firstOccurrence) {
				ostream << " ";
			}
			firstOccurrence = false;

			cond->print(ostream);
		}
	}
	ostream << ", ";
}

void Rule::printIPRewriter(std::ostream& ostream) {
	assert((_natIP != "-") || (_natPort != "-"));
	if (_target->getName() == "SNAT") {
		if (_natPort == "-") {
			ostream << " -> IPAddrPairRewriter(pattern " << _natIP << " - 0 0)";
		} else {
			ostream << " -> IPRewriter(pattern " << _natIP << " " << _natPort << " - - 0 0)";
		}
	} else if (_target->getName() == "DNAT") {
		if (_natPort == "-") {
			ostream << " -> IPAddrPairRewriter(pattern - " << _natIP << " 0 0)";
		} else {
			ostream << " -> IPRewriter(pattern - - " << _natIP << " " << _natPort << " 0 0)";
		}
	} else {
		assert(false);
	}
}

std::string Rule::getIpTablesText(){
	return _iptablesFormat;
}
