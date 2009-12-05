/**
 * @file PolicyFactory.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef POLICYFACTORY_H_
#define POLICYFACTORY_H_

//Standard
#include <string>
//Poco
//FireSim
#include "ConfigContent.h"

/**
 * @class ConditionFactory
 * Accordingly to the 'Factory Pattern' {@link ConditionFactory} is an interface for creating {@link ConditionFactory}.
 */
class PolicyFactory{
public:

	/**
	 * Destructor of PolicyFactory
	 */
	virtual ~PolicyFactory(){
	}

	/**
	 * Returns the unique instance of this class.
	 */
	static PolicyFactory* getInstance();

	/**
	 * Parse the arguments to a {@link Policy}
	 * @param name The name of the policy
	 */
	Policy parse(std::string policy);

private:
	/**
	 * Constructor of PolicyFactory
	 */
	PolicyFactory();

	static PolicyFactory* fInstance;
};


#endif /* POLICYFACTORY_H_ */
