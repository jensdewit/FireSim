/**
 * @file DstPortsCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef DSTPORTSCONDITION_H_
#define DSTPORTSCONDITION_H_

//Standard
//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "Condition.h"

class DstPortsCondition: public Condition {
public:
	DstPortsCondition(std::string dstPorts, bool reverse) : _dstPorts(dstPorts), _reverse(reverse) {
	}

	void print(std::ostream& stream) {
		//dstPorts is comma-separated
		Poco::StringTokenizer tokenizer(_dstPorts, ",", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		Poco::StringTokenizer::Iterator it = tokenizer.begin();

		//process first number or range
		size_t pos = it->find(":");
		if(pos==std::string::npos){
			stream << "dst port " << (_reverse ? "!= " : "") << *it;
		} else {
			//range detected
			std::string start = it->substr(0, pos);
			std::string end = it->substr(pos+1);
			if (_reverse) {
				stream << "(dst port < " <<  start << " or > " << end << ")";
			} else {
				stream << "dst port >= " <<  start << " and <= " << end;
			}
		}

		for(it++; it != tokenizer.end(); it++){
			 size_t pos = it->find(":");
			 if(pos==std::string::npos){
				 stream << (_reverse ? " and dst port != " : " or ") << *it;
			 } else {
				 //range detected
				 std::string start = it->substr(0, pos);
				 std::string end = it->substr(pos+1);
				 if (_reverse) {
					 stream << " and (dst port < " <<  start << " or > " << end << ")";
				 } else {
					 stream << " or >= " <<  start << " and <= " << end;
				 }
			 }
		}
	}

private:
	std::string _dstPorts;
	bool _reverse;
};

#endif /* DSTPORTSCONDITION_H_ */
