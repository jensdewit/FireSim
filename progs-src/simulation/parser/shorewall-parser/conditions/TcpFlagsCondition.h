/**
 * @file TcpFlagsCondition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef TCPFLAGSCONDITION_H_
#define TCPFLAGSCONDITION_H_

//Standard
#include <algorithm>
#include <string.h>

//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "Condition.h"

const std::string URG_FLAG = "URG"; //  Urgent Pointer field significant
const std::string ACK_FLAG = "ACK"; //  Acknowledgment field significant
const std::string PSH_FLAG = "PSH"; //  Push Function
const std::string RST_FLAG = "RST"; //  Reset the connection
const std::string SYN_FLAG = "SYN"; //  Synchronize sequence numbers
const std::string FIN_FLAG = "FIN"; //  No more data from sender

class TcpFlagsCondition: public Condition {
public:
	TcpFlagsCondition(std::string flagDeclarations, std::string setFlags, bool reverse) {
		_flagDeclarations = flagParser(flagDeclarations);
		_reverse = reverse;
		if (setFlags != "NONE"){
			//None flag is only allowed in "setFlags"
			_setFlags = flagParser(setFlags);
		}
	}

	void print(std::ostream& stream) {
		//process first flag
		std::vector<std::string>::iterator it = _flagDeclarations.begin();
		if (it != _flagDeclarations.end()){
			if (find(_setFlags.begin(), _setFlags.end(), *it) != _setFlags.end()) {
				//flag is set
				stream << (_reverse ? "not " : "") << *it;
			} else {
				stream << (_reverse ? "" : "not ") << *it;
			}
			it++;
		}

		//process other declared flags
		for(; it != _flagDeclarations.end(); it++) {
			if (find(_setFlags.begin(), _setFlags.end(), *it) != _setFlags.end()) {
				//flag is set
				stream << (_reverse ? " not " : " ") << *it;
			} else {
				stream << (_reverse ? " " : " not ") << *it;
			}
		}
	}

private:
	std::vector<std::string> _flagDeclarations;
	std::vector<std::string> _setFlags;
	bool _reverse;

	//helper function
	static std::vector<std::string> flagParser(std::string flags){
		std::vector<std::string> result;
		if (flags == "ALL"){
			result.push_back(UpToLow(URG_FLAG));
			result.push_back(UpToLow(ACK_FLAG));
			result.push_back(UpToLow(PSH_FLAG));
			result.push_back(UpToLow(RST_FLAG));
			result.push_back(UpToLow(SYN_FLAG));
			result.push_back(UpToLow(FIN_FLAG));

			//no other flags are tolerated
			return result;
		}
		//flag declarations is comma-separated
		Poco::StringTokenizer tokenizer(flags, ",", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		for (Poco::StringTokenizer::Iterator it = tokenizer.begin(); it != tokenizer.end(); it++) {
			if ((*it == URG_FLAG) || (*it == ACK_FLAG) || (*it == PSH_FLAG) || (*it == RST_FLAG) || (*it == SYN_FLAG) || (*it == FIN_FLAG)) {
				 std::locale loc;
				 char result2[10];
				 result.push_back(UpToLow(*it));
			} else {
				std::cout << "Flag of --tcp-flags = " << *it << " is not tolerated.";
				exit(1);
			}
		}
		return result;
	}

	//helper function
	static std::string UpToLow(std::string str) {
	    for (int i=0;i<strlen(str.c_str());i++)
	       if (str[i] >= 0x41 && str[i] <= 0x5A) {
	            str[i] = str[i] + 0x20;
	       }
	    return str;
	}

};

#endif /* TCPFLAGSCONDITION_H_ */
