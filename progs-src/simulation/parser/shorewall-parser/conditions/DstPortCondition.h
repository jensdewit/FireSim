/**
 * @file DstPortCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef DSTPORTCONDITION_H_
#define DSTPORTCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

class DstPortCondition: public Condition {
public:
	DstPortCondition(std::string dstPort, bool reverse) : _dstPort(dstPort), _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		size_t pos = _dstPort.find(":");
		if(pos==std::string::npos){
			stream << "dst port " <<  (_reverse ? "!= " : "") <<  _dstPort;
		} else {
			//range detected
			std::string start = _dstPort.substr(0, pos);
			std::string end =  _dstPort.substr(pos+1);
			if (_reverse) {
				stream << "dst port < " <<  start << " or > " << end;
			} else {
				stream << "dst port >= " <<  start << " and <= " << end;
			}
		}
	}

private:
	std::string _dstPort;
	bool _reverse;
};

#endif /* DSTPORTCONDITION_H_ */
