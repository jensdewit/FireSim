/**
 * @file ProtocolFactory.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <cstdlib>
#include <iostream>
//Poco
//FireSim
#include "ProtocolFactory.h"
#include "../../util/Util.h"

/**
 * Initialization of static members.
 */
ProtocolFactory* ProtocolFactory::fInstance = 0;

ProtocolFactory::ProtocolFactory() {
}

ProtocolFactory* ProtocolFactory::getInstance() {
	if (fInstance == 0) {
		//create the 1 instance of the object (singleton)
		fInstance = new ProtocolFactory();
	}
	return fInstance;
}

Protocol ProtocolFactory::parse(std::string protocol) {
	convertToLowerCase(protocol);
	removeWhitespace(protocol);
	Protocol p;
	if (protocol == "1" || protocol == "icmp") {
		p = ICMP;
	} else if (protocol == "6" || protocol == "tcp") {
		p = TCP;
	} else if (protocol == "17" || protocol == "udp") {
		p = UDP;
	} else {
		std::cout << "Unsupported protocol " << protocol << " specified." << std::endl;
		exit(1);
	}
	return p;
}
