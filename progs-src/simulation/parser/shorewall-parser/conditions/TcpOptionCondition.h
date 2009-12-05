/**
 * @file TcpOptionCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef TCPOPTIONCONDITION_H_
#define TCPOPTIONCONDITION_H_

//Standard
//Poco
//FireSim
#include "Condition.h"

/**
 * @class Match if TCP option set.
 */
class TcpOptionCondition: public Condition {
public:
	TcpOptionCondition(std::string number, bool reverse) : _number(number), _reverse(reverse){
	}

	void print(std::ostream& stream) {
		stream << (_reverse ? "not " : "") << "tcp opt " << _number;
	}

private:
	std::string _number;
	bool _reverse;
};

#endif /* TCPOPTIONCONDITION_H_ */
