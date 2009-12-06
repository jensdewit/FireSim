/**
 * @file ShorewallParser.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SHOREWALLPARSER_H_
#define SHOREWALLPARSER_H_

//Standard
#include <string>
#include <ostream>
//Poco
//FireSim
#include "Table.h"
#include "../network-parser/NetworkLayout.h"

/**
 * @class ShorewallParser
 * Accordingly to Singleton Pattern.
 * Parses a shorewall.compiled file.
 */
class ShorewallParser {
public:
	/**
	 * Destructor
	 */
	~ShorewallParser();


	/**
	 * Creates a unique instance of this class.
	 * @param path The file path to the shorewall.compiled file
	 * @param networkLayout The network layout
	 */
	static void createInstance(std::string path, NetworkLayout* networkLayout);

	/**
	 * Returns the unique instance of this class.
	 */
	static ShorewallParser* getInstance();

	/**
	 * Parse the nat table of the specified shorewall.compiled file.
	 */
	Table* parseNatTable();

	/**
	 * Parse the filter table of the specified shorewall.compiled file.
	 */
	Table* parseFilterTable();

	/**
	 * Parse the mangle table of the specified shorewall.compiled file.
	 */
	Table* parseMangleTable();

private:
	/**
	 * Private constructor. Use static method getInstance instead of constructor.
	 */
	ShorewallParser(std::string path, NetworkLayout* networkLayout);

	/**
	 * Private helper method.
	 * @param tableName Table to parse.
	 * @param config_path The directory where the configuration files are located.
	 */
	Table* parseTable(std::string tableName);

	static ShorewallParser* fInstance;
	NetworkLayout* _networkLayout;
	std::string _path;
};
#endif /* SHOREWALLPARSER_H_ */
