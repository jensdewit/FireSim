/**
 * @file Table.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef TABLE_H_
#define TABLE_H_

//Standard
#include <string>
#include <map>
#include <iostream>
//FireSim
#include "Chain.h"

/**
 * @class This class represents a collections of ipfilter chains.
 */
class Table {
public:
	/**
	 * Constructor
	 */
	Table();

	/**
	 * Destructor
	 */
	~Table();

	/**
	 * Add a chain to the collection.
	 * @param chain This is the chain.
	 */
	void add(Chain* chain);

	/**
	 * Get the chain with the specified name.
	 * @param name This is the name of the chain.
	 */
	Chain* get(std::string name);

//	/**
//	 * Verify whether a backtracker is needed for this table.
//	 * @return corresponding boolean.
//	 */
//	bool backtrackerNeeded();

	/**
	 * Print click classifier block
	 * @param ostream This is the output stream. The classifier block will be printed to this stream.
	 * @param prefix Concatenate this string in front of the click classifier name.
	 */
	void printClickClassifiers(std::ostream& ostream, std::string prefix);

	/**
	 * Print click simulation block
	 * @param ostream This is the output stream. The simulation block will be printed to this stream.
	 */
	void printClickSimulation(std::ostream& ostream, std::string prefix);

	/**
	 * Print click trace simulation block
	 * @param ostream This is the output stream. The trace simulation block will be printed to this stream.
	 */
	void printClickTraceSimulation(std::ostream& ostream, std::string prefix);

	/**
	 * Print click pretty printers block
	 * @param ostream This is the output stream. The pretty print block will be printed to this stream.
	 */
	void printPrettyPrinters(std::ostream& ostream, std::string prefix);

private:
	std::map<std::string, Chain*> _map;
};

#endif /* TABLE_H_ */
