/**
 * @file TtlGtCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef TTLGTCONDITION_H_
#define TTLGTCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

/**
 * @class This condition matches the time to live field in the IP header.
 *  Matches only if TTL is greater than the given TTL value.
 */
class TtlGtCondition: public Condition {
public:
	TtlGtCondition(std::string ttl) : _ttl(ttl){
		//TODO assert that TTL is a value between 0 and 255.
	}

	void print(std::ostream& stream) {
		stream << "ip ttl >" << _ttl;
	}

private:
	std::string _ttl;
};

#endif /* TTLGTCONDITION_H_ */
