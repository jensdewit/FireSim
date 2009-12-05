/**
 * @file RuleParser.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <iostream>
#include "assert.h"

//Poco
#include "Poco/Logger.h"
#include "Poco/StringTokenizer.h"

//Firesim
#include "RuleParser.h"
#include "Chain.h"
#include "Rule.h"
#include "conditions/Condition.h"
#include "conditions/ConditionFactory.h"
#include "../../util/Util.h"

using std::cout;
using std::endl;

/**
 * Initialization of static members.
 */
RuleParser* RuleParser::fInstance = 0;

RuleParser::RuleParser() {
}

RuleParser* RuleParser::getInstance() {
	if (fInstance == 0) {
		//create the 1 instance of the object (singleton)
		fInstance = new RuleParser();
	}
	return fInstance;
}

void RuleParser::parse(std::string rules, Table* table, NetworkLayout* networkLayout){
	//Tokenize rules
	Poco::StringTokenizer rulesTokenizer(rules, "\n", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	Poco::Logger::get("ConsoleLogger").debug("nr of rules recognized = " + itoa(rulesTokenizer.count()));
	for(Poco::StringTokenizer::Iterator it = rulesTokenizer.begin(); it != rulesTokenizer.end(); it++){
		std::string ruleString = *it;
		if ((*it)[it->size()-1]=='\r'){
			ruleString = it->substr(0, it->size()-1);
		}
		Poco::Logger::get("ConsoleLogger").debug("rule processing: " + ruleString);
		//Tokenize parameters
		Poco::StringTokenizer paramTokenizer(ruleString, " ", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		int nrOfTokens = paramTokenizer.count();

		ConditionFactory* fact = ConditionFactory::getInstance(networkLayout);
		Poco::Logger::get("ConsoleLogger").debug("=> nr of params recognized = " + itoa(nrOfTokens -4));
		//ignore first 2 tokens (equals -A and chain name) and the last 2 (equals -j chain name)
		std::vector<std::string> conditionList;
		bool jumpFound = false;
		Chain* target = 0;
		bool natNeeded = false;
		std::string natIP = "-";
		std::string natPort = "-";
		for (int i = 2; i < (nrOfTokens); i++) {
			if ((paramTokenizer[i]=="-j") || (paramTokenizer[i]=="--jump")) {
				//jump clause found
				jumpFound = true;
				target = table->get(paramTokenizer[i+1]);
				//TODO masquerade
				if ((paramTokenizer[i+1] == "DNAT") || (paramTokenizer[i+1] == "SNAT")) {
					natNeeded = true;
					std::string nat = paramTokenizer[i+3];
					size_t pos = nat.find(":"); //split ip adress and port
					if (pos == std::string::npos) {
						natIP = nat;
					} else {
						natIP = nat.substr(0, pos);
						natPort = nat.substr(pos+1);
					}
				}
				break;
			}
			conditionList.push_back(paramTokenizer[i]);

//			Poco::Logger::get("ConsoleLogger").debug("rule condition constructed: " + paramTokenizer[i] + " and " + paramTokenizer[i+1]);
//			Condition*  cond = fact->parse(paramTokenizer[i], paramTokenizer[i+1]);
//			if (cond) {
//				conditions.push_back(cond);
//			}
		}
		assert(jumpFound); //rule is not complete without a jump clause.

		std::vector<Condition*> conditions = fact->parse(conditionList);

//		cout << "All conditions for this rule processed"<<endl;
//
//		//Construct the rule with all parsed conditions
//		if (!target->isFinal()){
//			std::cout << "Target Chain " << target->getName() << " is not final!"<<std::endl;
//		}
		Rule* rule;
		if (natNeeded) {
			rule = new Rule(ruleString, conditions, target, natIP, natPort);
		} else {
			rule = new Rule(ruleString, conditions, target);
		}
		//corresponding chain
		Chain* chain = table->get(paramTokenizer[1]);
		//update the chain
		chain->add(rule);

		if(target->getName() != "ULOG" && target->getName() != "SNAT"
			&& target->getName() != "DNAT" && target->getName() != "MASQUERADE") {
			target->setUsed();
		}
	}
}
