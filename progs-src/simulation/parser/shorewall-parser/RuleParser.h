/**
 * @file RuleParser.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef RULEPARSER_H_
#define RULEPARSER_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Table.h"
#include "../network-parser/NetworkLayout.h"

/**
 * @class RuleParser
 * Accordingly to Singleton Pattern.
 * Parses a shorewall.compiled file.
 */
class RuleParser {
public:

	/**
	 * Returns the unique instance of this class.
	 */
	static RuleParser* getInstance();

	/**
	 * Parse the specified ipfilter rules.
	 * @pre table may not be null.
	 * @pre The table must contain all declared chains used in the rules.
	 * @param rules This are the rules that must be parsed.
	 * @param table This is the collections wich contains all known chains.
	 * @param networkLayout This represents the layout of the network.
	 * All parsed rules will be added to the corresponding chain.
	 */
	void parse(std::string rules, Table* table, NetworkLayout* networkLayout);

private:

	/**
	 * Private constructor. Use static method getInstance instead of constructor.
	 */
	RuleParser();

	static RuleParser* fInstance;

};

#endif /* RULEPARSER_H_ */
