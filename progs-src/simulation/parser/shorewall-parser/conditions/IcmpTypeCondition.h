/**
 * @file IcmpTypeCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef ICMPTYPECONDITION_H_
#define ICMPTYPECONDITION_H_

//Standard
#include <string>
//Poco
//FireSim
#include "LowLevelCondition.h"
#include "../../../util/Util.h"

/*
Valid ICMP Types:
any
echo-reply (pong)
destination-unreachable
   network-unreachable
   host-unreachable
   protocol-unreachable
   port-unreachable
   fragmentation-needed
   source-route-failed
   network-unknown
   host-unknown
   network-prohibited
   host-prohibited
   TOS-network-unreachable
   TOS-host-unreachable
   communication-prohibited
   host-precedence-violation
   precedence-cutoff
source-quench
redirect
   network-redirect
   host-redirect
   TOS-network-redirect
   TOS-host-redirect
echo-request (ping)
router-advertisement
router-solicitation
time-exceeded (ttl-exceeded)
   ttl-zero-during-transit
   ttl-zero-during-reassembly
parameter-problem
   ip-header-bad
   required-option-missing
timestamp-request
timestamp-reply
address-mask-request
address-mask-reply
*/

/**
 * @class This extension can be used if ‘--protocol icmp’ is specified.
 * This allows specification of the ICMP type, which can be a numeric ICMP type, or one of the ICMP type names shown by the command iptables -p icmp -h
 *
 */
class IcmpTypeCondition: public LowLevelCondition {
public:
	IcmpTypeCondition(std::string type, bool reverse) : _type(type), _reverse(reverse){
		//TODO convert the ICMP type names shown by the command iptables -p icmp -h to the numeric equivalent
	}

	void print(std::ostream& stream) {
		size_t pos = _type.find("/");
		char type[8];
		decimalToHex(stringToInt(_type.substr(0, pos)), type);
		stream << (_reverse ? "!" : "") << "34/" << type[1] << type[0];
		if (pos != std::string::npos) {
			char code[8];
			decimalToHex(stringToInt(_type.substr(pos+1)), code);
			stream << code[1] << code[0];
		}
	}

private:
	std::string _type;
	bool _reverse;
};

#endif /* ICMPTYPECONDITION_H_ */
