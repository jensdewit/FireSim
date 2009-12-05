/**
 * @file TosCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef TOSCONDITION_H_
#define TOSCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

/**
 * @class This condition matches the 8 bits of Type of Service field in the IP header (ie. including the precedence bits).
 */
class TosCondition: public Condition {
public:
	TosCondition(std::string tos) : _tos(tos){
	}

	void print(std::ostream& stream) {
		stream << "ip tos " << _tos;
	}

private:
	std::string _tos;
};

#endif /* TOSCONDITION_H_ */
