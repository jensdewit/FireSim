/**
 * @file InInterfaceCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef ININTERFACECONDITION_H_
#define ININTERFACECONDITION_H_

//Standard
#include <string>
//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "LowLevelCondition.h"
#include "../../network-parser/NetworkLayout.h"

class InInterfaceCondition : public LowLevelCondition {
public:
	InInterfaceCondition(std::string interface, NetworkLayout* networkLayout, bool reverse) :
		_interface(interface), _networkLayout(networkLayout), _reverse(reverse){
	}

	void print(std::ostream& stream) {
		std::string macAddress = _networkLayout->getMacAddress(_interface);
		Poco::StringTokenizer macTokenizer(macAddress, ":", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		stream << (_reverse ? "!" : "") << "0/";
		for(int index = 0; index < macTokenizer.count(); index++){
			stream << macTokenizer[index];
		}
	}

private:
	std::string _interface;
	NetworkLayout* _networkLayout;
	bool _reverse;
};

#endif /* ININTERFACECONDITION_H_ */
