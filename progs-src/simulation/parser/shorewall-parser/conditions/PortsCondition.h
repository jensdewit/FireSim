/**
 * @file PortsCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef PORTSCONDITION_H_
#define PORTSCONDITION_H_

//Standard
//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "Condition.h"

class PortsCondition: public Condition {
public:
	PortsCondition(std::string ports, bool reverse) : _ports(ports), _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		//dstPorts is comma-separated
		Poco::StringTokenizer tokenizer(_ports, ",", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		Poco::StringTokenizer::Iterator it = tokenizer.begin();

		//process first number or range
		size_t pos = it->find(":");
		if(pos==std::string::npos){
			stream << "port " << (_reverse ? "!= " : "") << *it;
		} else {
			//range detected
			std::string start = it->substr(0, pos);
			std::string end = it->substr(pos+1);
			if (_reverse) {
				stream << "(port < " <<  start << " or > " << end << ")";
			} else {
				stream << "port >= " <<  start << " and <= " << end;
			}
		}

		for(it++; it != tokenizer.end(); it++){
			size_t pos = it->find(":");
			if(pos==std::string::npos){
				 stream << (_reverse ? " and port != " : " or ") << *it;
			} else {
				//range detected
				std::string start = it->substr(0, pos);
				std::string end = it->substr(pos+1);
				if (_reverse) {
					stream << " and (port < " <<  start << " or > " << end << ")";
				} else {
					stream << " or >= " <<  start << " and <= " << end;
				}
			}
		}
	}

private:
	std::string _ports;
	bool _reverse;
};

#endif /* PORTSCONDITION_H_ */
