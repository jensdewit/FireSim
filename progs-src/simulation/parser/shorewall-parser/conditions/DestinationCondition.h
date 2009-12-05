/**
 * @file DestinationCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef DESTINATIONCONDITION_H_
#define DESTINATIONCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

class DestinationCondition: public Condition {
public:
	DestinationCondition(std::string dstIP, bool reverse) : _dstIP(dstIP), _reverse(reverse){
	}

	void print(std::ostream& stream) {
		size_t pos = _dstIP.find("/");
		if (pos == std::string::npos) {
			stream << "dst host " << (_reverse ? "!= " : "") << _dstIP;
		} else {
			stream << "dst net " << (_reverse ? "!= " : "") << _dstIP;
		}

	}

private:
	std::string _dstIP;
	bool _reverse;
};

#endif /* DESTINATIONCONDITION_H_ */
