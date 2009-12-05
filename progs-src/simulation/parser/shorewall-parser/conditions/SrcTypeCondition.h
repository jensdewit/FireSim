/**
 * @file SrcTypeCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SRCTYPECONDITION_H_
#define SRCTYPECONDITION_H_

//Standard
#include <string>
#include "assert.h"
#include <vector>
//Poco
//FireSim
#include "Condition.h"
#include "../../network-parser/NetworkLayout.h"

class SrcTypeCondition : public Condition {
public:
	SrcTypeCondition(std::string type, NetworkLayout* networkLayout) : _type(type), _networkLayout(networkLayout) {
	}

	void print(std::ostream& stream) {
		assert(_type == "BROADCAST"); //No other types are currently supported
		//Check whether the destination of the packet corresponds to any of the broadcast address of the interface of the firewall
		std::vector<std::string> broadcastAddresses = _networkLayout->getBroadcastAddresses();
		assert(!broadcastAddresses.empty()); //some broadcast addresses must be defined
		stream << "src host " << broadcastAddresses[0] << " or ";
		for (std::vector<std::string>::iterator it = broadcastAddresses.begin(); it != broadcastAddresses.end(); it++){
			if((it+1)==broadcastAddresses.end()){
				//process last known broadcast address
				stream << *it;
			} else {
				stream << *it << " or ";
			}
		}
	}

private:
	std::string _type;
	NetworkLayout* _networkLayout;
};

#endif /* SRCTYPECONDITION_H_ */
