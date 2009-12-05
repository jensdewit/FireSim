/**
 * @file OutInterfaceCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef OUTINTERFACECONDITION_H_
#define OUTINTERFACECONDITION_H_

//Standard
#include <string>
//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "LowLevelCondition.h"
#include "../../network-parser/NetworkLayout.h"

class OutInterfaceCondition : public LowLevelCondition {
public:
	OutInterfaceCondition(std::string interface, NetworkLayout* networkLayout, bool reverse) :
		_interface(interface), _networkLayout(networkLayout), _reverse(reverse){
	}

	void print(std::ostream& stream) {
		std::string macAddress = _networkLayout->getMacAddress(_interface);
		Poco::StringTokenizer macTokenizer(macAddress, ":", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		stream << (_reverse ? "!" : "") << "6/";
		for(int index = 0; index < macTokenizer.count(); index++){
			stream << macTokenizer[index];
		}
	}

private:
	std::string _interface;
	NetworkLayout* _networkLayout;
	bool _reverse;
};

#endif /* OUTINTERFACECONDITION_H_ */
