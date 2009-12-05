/**
 * @file StateCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef STATECONDITION_H_
#define STATECONDITION_H_

//Standard
//Poco
//FireSim
#include "IgnorableCondition.h"

class StateCondition : public IgnorableCondition {
public:
	StateCondition(std::string values) : _values(values){
	}

	void print(std::ostream& stream) {
		stream << "IGNORED" << std::endl;
	}

private:
	std::string _values;
};

#endif /* STATECONDITION_H_ */
