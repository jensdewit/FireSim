/**
 * @file SynCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SYNCONDITION_H_
#define SYNCONDITION_H_

//Standard
//Poco
//FireSim
#include "Condition.h"

/**
 * @class
 *  Only match TCP packets with the SYN bit set and the ACK,RST and FIN bits cleared.
 *  Such packets are used to request TCP connection  initiation;
 *  for example, blocking such packets coming in an interface will prevent incoming TCP connections, but outgoing TCP connections will be unaffected.
 *  It is equivalent to --tcp-flags SYN,RST,ACK,FIN SYN.  If the "!" flag precedes  the  "--syn",  the  sense  of  the  option  is inverted.
 */
class SynCondition: public Condition {
public:
	SynCondition(bool reverse): _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		if (_reverse) {
			stream << "not syn rst ack fin";
		} else {
			stream << "syn not rst not ack not fin";
		}
	}

private:
	bool _reverse;
};

#endif /* SYNCONDITION_H_ */
