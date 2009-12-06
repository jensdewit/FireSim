/**
 * @file ConfigParser.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 * This header file introduces some xml parsers.
 * Parsing (similar to deserialization) is the process of transforming
 * xml to the memory representation of an object.
 */

#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

//Standard
#include <vector>

//Poco
#include "Poco/DOM/Document.h"

//FireSim
#include "ConfigContent.h"
#include "../network-parser/NetworkLayout.h"


/**
 * @class ConfigParser
 * Accordingly to Singleton Pattern.
 * Deserialize xml to {@link ConfigContent}.
 */
class ConfigParser {
public:
	/**
	 * Creates a unique instance of this class.
	 * @param path The file path of the config files
	 */
	static void createInstance(std::string path);

	/**
	 * Returns the unique instance of this class.
	 */
	static ConfigParser* getInstance();

	/**
	 * Conversion from xml to content-object.
	 */
	void parse(Poco::XML::Document*  xmlNode, NetworkLayout* networkLayout);

	/**
	 * Print click traffic blocks
	 * @param ostream This is the output stream. The traffic blocks will be printed to this stream.
	 */
	void printClickTraffic(std::ostream& ostream, NetworkLayout* networkLayout);

private:
	/**
	 * Private constructor. Use static method getInstance instead of constructor.
	 * @param path The file path of the config files
	 */
	ConfigParser(std::string path);

	std::string _path;
	std::vector<ConfigContent*> _content;

	static ConfigParser* fInstance;

};

#endif /* CONFIGPARSER_H_ */
