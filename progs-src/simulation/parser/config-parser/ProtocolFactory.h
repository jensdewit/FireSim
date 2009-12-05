/**
 * @file ProtocolFactory.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef PROTOCOLFACTORY_H_
#define PROTOCOLFACTORY_H_

//Standard
#include <string>
//Poco
//FireSim
#include "ConfigContent.h"

/**
 * @class ConditionFactory
 * Accordingly to the 'Factory Pattern' {@link ConditionFactory} is an interface for creating {@link ConditionFactory}.
 */
class ProtocolFactory{
public:

	/**
	 * Destructor of PolicyFactory
	 */
	virtual ~ProtocolFactory(){
	}

	/**
	 * Returns the unique instance of this class.
	 */
	static ProtocolFactory* getInstance();

	/**
	 * Parse the arguments to a {@link Protocol}
	 * @param protocol The name of the protocol
	 */
	Protocol parse(std::string policy);

private:
	/**
	 * Constructor of ProtocolFactory
	 */
	ProtocolFactory();

	static ProtocolFactory* fInstance;
};

#endif /* PROTOCOLFACTORY_H_ */
