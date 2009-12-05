/**
 * @file TtlEqCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef TTLEQCONDITION_H_
#define TTLEQCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

/**
 * @class This condition matches the time to live field in the IP header.
 */
class TtlEqCondition: public Condition {
public:
	TtlEqCondition(std::string ttl) : _ttl(ttl){
		//TODO assert that TTL is a value between 0 and 255.
	}

	void print(std::ostream& stream) {
		stream << "ip ttl " << _ttl;
	}

private:
	std::string _ttl;
};

#endif /* TTLEQCONDITION_H_ */
