/**
 * @file ConditionFactory.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef CONDITIONFACTORY_H_
#define CONDITIONFACTORY_H_

//Standard
#include <string>
#include <vector>
//Poco
//FireSim
#include "Condition.h"
#include "../../network-parser/NetworkLayout.h"

/**
 * @class ConditionFactory
 * Accordingly to the 'Factory Pattern' {@link ConditionFactory} is an interface for creating {@link ConditionFactory}.
 */
class ConditionFactory{
public:

	/**
	 * Destructor of CommandFactory
	 */
	virtual ~ConditionFactory(){}

	/**
	 * Returns the unique instance of this class.
	 * @param networkLayout This represents the layout of the network.
	 */
	static ConditionFactory* getInstance(NetworkLayout* networkLayout);

	/**
	 * Parse the arguments to a {@link Condition}
	 * @param conditionList Summation of names and values of the condition of a rule.
	 */
	std::vector<Condition*> parse(std::vector<std::string> conditionList);

private:
	/**
	 * Constructor of ConditionFactory
	 * @param networkLayout Pointer to network layout
	 */
	ConditionFactory(NetworkLayout* networkLayout);

	/**
	 * Parse the arguments to a {@link Condition}
	 * @param name This is the name of the condition
	 * @param values This is the ipfilter specified constraints corresponding to the condition.
	 */
	Condition* parseCondition(std::string name, std::vector<std::string> values, bool reverse);

	NetworkLayout* _networkLayout;
	std::map<std::string, int> _parameterMap;

	static ConditionFactory* fInstance;
};

#endif /* CONDITIONFACTORY_H_ */
