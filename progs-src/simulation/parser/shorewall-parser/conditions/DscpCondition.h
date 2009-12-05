/**
 * @file DscpCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef DSCPCONDITION_H_
#define DSCPCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

/**
 * @class This condition matches the 6 bit DSCP field within the TOS field in the IP header.
 * DSCP has superseded TOS within the IETF.
 */
class DscpCondition: public Condition {
public:
	DscpCondition(std::string value) : _value(value){
		//TODO assert that DSCP is a value between 0 and 63.
	}

	void print(std::ostream& stream) {
		stream << "ip dscp " << _value;
	}

private:
	std::string _value;
};

#endif /* DSCPCONDITION_H_ */
