/**
 * @file NetworkParser.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 * This header file introduces some xml parsers.
 * Parsing (similar to deserialization) is the process of transforming
 * xml to the memory representation of an object.
 */

#ifndef NETWORKPARSER_H_
#define NETWORKPARSER_H_

//Standard
#include <map>

//Poco
#include "Poco/DOM/Document.h"

//FireSim
#include "NetworkContent.h"
#include "NetworkLayout.h"

/**
 * @class NetworkParser
 * Accordingly to Singleton Pattern.
 * Deserialize xml to {@link NetworkLayout}.
 */
class NetworkParser {
public:
	/**
	 * Returns a reference to a {@link NetworkParser}
	 */
	static NetworkParser* getInstance();

	/**
	 * Conversion from xml to content-object.
	 */
	NetworkLayout* parse(Poco::XML::Document* xmlNode);

private:
	/**
	 * Private constructor. Use static method getInstance instead of constructor.
	 */
	NetworkParser();

	static NetworkParser* fInstance;

};

#endif /* NETWORKPARSER_H_ */
