/**
 * @file SourceCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SOURCECONDITION_H_
#define SOURCECONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

class SourceCondition: public Condition {
public:
	SourceCondition(std::string srcIP, bool reverse) : _srcIP(srcIP), _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		size_t pos = _srcIP.find("/");
		if (pos == std::string::npos) {
			stream << "src host " << (_reverse ? "!= " : "") << _srcIP;
		} else {
			stream << "src net " << (_reverse ? "!= " : "") << _srcIP;
		}
	}

private:
	std::string _srcIP;
	bool _reverse;
};

#endif /* SOURCECONDITION_H_ */
