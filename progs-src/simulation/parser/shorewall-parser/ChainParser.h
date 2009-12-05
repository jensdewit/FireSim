/**
 * @file ChainParser.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef CHAINPARSER_H_
#define CHAINPARSER_H_

#include <string>
#include "Table.h"

/**
 * @class ChainParser
 * Accordingly to Singleton Pattern.
 * Parses a shorewall.compiled file.
 */
class ChainParser {
public:

	/**
	 * Returns the unique instance of this class.
	 */
	static ChainParser* getInstance();

	/**
	 * Parse the specified ipfilter chains.
	 * @pre table may not be null.
	 * @param chains This are the chains that must be parsed.
	 * @param table This is the table which will control the parsed chains.
	 */
	void parse(std::string chains, Table* table);

private:

	/**
	 * Private constructor. Use static method getInstance instead of constructor.
	 */
	ChainParser();

	static ChainParser* fInstance;
};

#endif /* CHAINPARSER_H_ */
