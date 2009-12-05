/**
 * @file ProtocolCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef PROTOCOLCONDITION_H_
#define PROTOCOLCONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "Condition.h"

const std::string ICMP_PROTOCOL = "icmp";
const std::string ICMP_PROTOCOL_NR = "1";
const std::string UDP_PROTOCOL = "udp";
const std::string UDP_PROTOCOL_NR = "17";
const std::string TCP_PROTOCOL = "tcp";
const std::string TCP_PROTOCOL_NR = "6";

class ProtocolCondition: public Condition {
public:
	ProtocolCondition(std::string protocol, bool reverse) : _reverse(reverse) {
		if (protocol == ICMP_PROTOCOL) {
			_protocol = ICMP_PROTOCOL_NR;
		} else if (protocol == TCP_PROTOCOL) {
			_protocol = TCP_PROTOCOL_NR;
		} else if (protocol == UDP_PROTOCOL) {
			_protocol = UDP_PROTOCOL_NR;
		} else {
			_protocol = protocol;
		}
	}

	void print(std::ostream& stream) {
		stream << "ip proto " << (_reverse ? "!= " : "") << _protocol;
	}

private:
	std::string _protocol;
	bool _reverse;
};


#endif /* PROTOCOLCONDITION_H_ */
