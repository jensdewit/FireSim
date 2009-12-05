/**
 * @file SrcPortsCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SRCPORTSCONDITION_H_
#define SRCPORTSCONDITION_H_

//Standard
//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "Condition.h"

class SrcPortsCondition: public Condition {
public:
	SrcPortsCondition(std::string srcPorts, bool reverse) : _srcPorts(srcPorts), _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		//dstPorts is comma-separated
		Poco::StringTokenizer tokenizer(_srcPorts, ",", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		Poco::StringTokenizer::Iterator it = tokenizer.begin();

		//process first number or range
		size_t pos = it->find(":");
		if(pos==std::string::npos){
			stream << "src port " << (_reverse ? "!= " : "") << *it;
		} else {
			//range detected
			std::string start = it->substr(0, pos);
			std::string end = it->substr(pos+1);
			if (_reverse) {
				stream << "(src port < " <<  start << " or > " << end << ")";
			} else {
				stream << "src port >= " <<  start << " and <= " << end;
			}
		}

		for(it++; it != tokenizer.end(); it++){
			size_t pos = it->find(":");
			if(pos==std::string::npos){
				stream << (_reverse ? " and src port != " : " or ") << *it;
			} else {
				//range detected
				std::string start = it->substr(0, pos);
				std::string end = it->substr(pos+1);
				if (_reverse) {
					stream << " and (src port < " <<  start << " or > " << end << ")";
				} else {
					stream << " or >= " <<  start << " and <= " << end;
				}
			}
		}
	}

private:
	std::string _srcPorts;
	bool _reverse;
};

#endif /* SRCPORTSCONDITION_H_ */
