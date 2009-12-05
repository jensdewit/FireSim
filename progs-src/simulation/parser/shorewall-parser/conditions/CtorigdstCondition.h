/**
 * @file CtorigdstCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef CTORIGDSTCONDITION_H_
#define CTORIGDSTCONDITION_H_

//Standard
//Poco
//FireSim
#include "IgnorableCondition.h"

class CtorigdstCondition : public IgnorableCondition {
public:
	CtorigdstCondition(std::string values) : _values(values){
	}

	void print(std::ostream& stream) {
		stream << "IGNORED" << std::endl;
	}

private:
	std::string _values;
};

#endif /* CTORIGDSTCONDITION_H_ */
