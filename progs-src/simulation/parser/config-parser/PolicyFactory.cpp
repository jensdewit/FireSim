/**
 * @file PolicyFactory.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <cstdlib>
#include <iostream>
//Poco
//FireSim
#include "PolicyFactory.h"
#include "../../util/Util.h"

/**
 * Initialization of static members.
 */
PolicyFactory* PolicyFactory::fInstance = 0;

PolicyFactory::PolicyFactory() {
}

PolicyFactory* PolicyFactory::getInstance() {
	if (fInstance == 0) {
		//create the 1 instance of the object (singleton)
		fInstance = new PolicyFactory();
	}
	return fInstance;
}

Policy PolicyFactory::parse(std::string policy) {
	convertToLowerCase(policy);
	removeWhitespace(policy);
	Policy p;
	if (policy == "accept") {
		p = ACCEPT;
	} else if (policy == "reject") {
		p = REJECT;
	} else if (policy == "drop") {
		p = DROP;
	} else {
		std::cout << "Unsupported policy " << policy << " specified." << std::endl;
		exit(1);
	}
	return p;
}
