/**
 * @file ShorewallParser.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standaard
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "assert.h"
//Poco
#include "Poco/Logger.h"
#include "Poco/StringTokenizer.h"
//FireSim
#include "../ApplicationConstants.h"
#include "Table.h"
#include "ChainParser.h"
#include "RuleParser.h"
#include "ShorewallParser.h"
#include "ScriptResolver.h"

using std::cout;
using std::endl;

/**
 * Initialization of static members.
 */
ShorewallParser* ShorewallParser::fInstance = 0;

ShorewallParser::ShorewallParser(std::string path, NetworkLayout* networkLayout) :
	_networkLayout(networkLayout), _path(path) {
}

ShorewallParser::~ShorewallParser(){
	delete _networkLayout;
}

void ShorewallParser::createInstance(std::string path, NetworkLayout* networkLayout) {
	if (fInstance == 0) {
		fInstance = new ShorewallParser(path, networkLayout);
	}
}

ShorewallParser* ShorewallParser::getInstance() {
	assert(fInstance);
	return fInstance;
}

Table* ShorewallParser::parseTable(std::string tableName) {
	std::ifstream stream;
	stream.open((_path + SHOREWALLCOMPILED_FILENAME).c_str(), std::ios::binary | std::ios::in);

	//path must be correct
	assert(stream.is_open());

	// determine file length
	stream.seekg(0, std::ios::end);
	int length = stream.tellg();
	stream.seekg(0, std::ios::beg);

	// read the file
	char buffer[length];
	stream.read(buffer, length);
	stream.close();

	// find the useful part (filter table)
	std::string input(buffer);

	size_t posTable = input.find(tableName);
	if (posTable != std::string::npos) {
		input = input.substr(posTable + tableName.length()+1);
	} else {
		cout << "Unacceptable file structure! Could not find start of the " << tableName.substr(1) << " table. Aborting." << endl;
		exit(1);
	}
	size_t posCommit = input.find("COMMIT");
	size_t posEOFstart = input.find("__EOF__");
	if (posCommit != std::string::npos) {
		if (posEOFstart < posCommit) {
			std::string inputs = "";
			size_t posEOFstop = 0;
			do {
				//add the substring between the previous EOFstop and the current EOFstart to inputs
				inputs += input.substr(posEOFstop, posEOFstart - posEOFstop);
				//update EOFstop
				posEOFstop = input.find("__EOF__",
						posEOFstart + std::string("__EOF__").length()) + std::string("__EOF__)").length();
				//extract the script part in a substring
				std::string script = input.substr(posEOFstart, posEOFstop - posEOFstart);
				//remove the starting EOF and the last line containing the ending EOF
				Poco::StringTokenizer scriptTokenizer(script, "\n", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
				script = "";
				for(Poco::StringTokenizer::Iterator it = scriptTokenizer.begin()+1; it != scriptTokenizer.end()-1; it++){

					script += *it;
					if ((*it)[it->size()-1]=='\r'){
						script = script.substr(0, script.size()-1);
					}
					script += "\n";
				}
				//debug print
				Poco::Logger::get("ConsoleLogger").debug("script found:\n " + script + "\n");
				ScriptResolver scriptResolver(script);
				inputs += scriptResolver.resolve(_path);
				//update EOFstart
				posEOFstart = input.find("__EOF__", posEOFstop + std::string("__EOF__").length());
			} while (posEOFstart < posCommit);
			input = inputs + input.substr(posEOFstop, posCommit - posEOFstop);
		} else {
			input = input.substr(0, posCommit);
		}
	} else {
		cout << "Unacceptable file structure! Could not find end of the " << tableName.substr(1) << " table. Aborting." << endl;
		exit(1);
	}

	// extract the chains and rules
	std::string chains;
	std::string rules;
	posCommit = input.find("-A");
	if (posCommit != std::string::npos) {
		chains = input.substr(0, posCommit);
		rules = input.substr(posCommit);
	} else {
		chains = input;
		rules = "";
	}

	Table* table = new Table();

	ChainParser* chainParser = ChainParser::getInstance();
	chainParser->parse(chains, table);

	RuleParser* ruleParser = RuleParser::getInstance();
	ruleParser->parse(rules, table, _networkLayout);

	return table;
}

Table* ShorewallParser::parseFilterTable() {
	return parseTable("*filter");
}

Table* ShorewallParser::parseNatTable() {
	return parseTable("*nat");
}

Table* ShorewallParser::parseMangleTable() {
	return parseTable("*mangle");
}
