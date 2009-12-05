/**
 * @file ChainParser.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <iostream>
#include <vector>
#include "assert.h"

//Poco
#include "Poco/Logger.h"
#include "Poco/StringTokenizer.h"

//Firesim
#include "../util/Util.h"
#include "Chain.h"
#include "Table.h"
#include "ChainParser.h"

using std::cout;
using std::endl;

/**
 * Initialization of static members.
 */
ChainParser* ChainParser::fInstance = 0;

ChainParser::ChainParser() {
}

ChainParser* ChainParser::getInstance() {
	if (fInstance == 0) {
		//create the 1 instance of the object (singleton)
		fInstance = new ChainParser();
	}
	return fInstance;
}

void ChainParser::parse(std::string chains, Table* table){
	assert(table); //table may not be null
	//Tokenize chains
	Poco::StringTokenizer chainsTokenizer(chains, "\n", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	for(Poco::StringTokenizer::Iterator it = chainsTokenizer.begin(); it != chainsTokenizer.end(); it++){
		std::string chain = *it;
		if ((*it)[it->size()-1]=='\r'){
			chain = it->substr(0, it->size()-1);
		}
		//Tokenize chain
		Poco::StringTokenizer chainTokenizer(chain, ":", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		//Tokenize parameters
		Poco::StringTokenizer paramTokenizer(chainTokenizer[0], " ", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		bool usedChain = false;
		if(paramTokenizer[0] == "PREROUTING" || paramTokenizer[0] == "POSTROUTING" || paramTokenizer[0] == "INPUT" ||
				paramTokenizer[0] == "FORWARD" || paramTokenizer[0] == "OUTPUT") {
			usedChain = true;
		}
		if(paramTokenizer[1] == "-") {
			Poco::Logger::get("ConsoleLogger").debug("chain constructed: " + paramTokenizer[0]);
			table->add(new Chain(paramTokenizer[0], false, usedChain));
		} else {
			Poco::Logger::get("ConsoleLogger").debug("chain constructed: " + paramTokenizer[0] + " and " + paramTokenizer[1]);
			table->add(new Chain(paramTokenizer[0], paramTokenizer[1], false, usedChain));
		}
	}
}
