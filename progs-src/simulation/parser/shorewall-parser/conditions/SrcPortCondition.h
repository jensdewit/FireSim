/**
 * @file SrcPortCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SRCPORTCONDITION_H_
#define SRCPORTCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

class SrcPortCondition: public Condition {
public:
	SrcPortCondition(std::string srcPort, bool reverse) : _srcPort(srcPort), _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		size_t pos = _srcPort.find(":");
		if(pos==std::string::npos){
			stream << "src port " <<  (_reverse ? "!= " : "") <<  _srcPort;
		} else {
			//range detected
			std::string start = _srcPort.substr(0, pos);
			std::string end =  _srcPort.substr(pos+1);
			if (_reverse) {
				stream << "src port < " <<  start << " or > " << end;
			} else {
				stream << "src port >= " <<  start << " and <= " << end;
			}
		}
	}

private:
	std::string _srcPort;
	bool _reverse;
};

#endif /* SRCPORTCONDITION_H_ */
