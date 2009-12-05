/**
 * @file ConditionFactory.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <cstdlib>
#include <iostream>

//Poco
#include "Poco/Logger.h"

//FireSim
#include "ConditionFactory.h"
#include "ProtocolCondition.h"
#include "SourceCondition.h"
#include "SrcPortCondition.h"
#include "DestinationCondition.h"
#include "DstPortCondition.h"
#include "SrcPortsCondition.h"
#include "DstPortsCondition.h"
#include "PortsCondition.h"
#include "InInterfaceCondition.h"
#include "OutInterfaceCondition.h"
#include "TcpFlagsCondition.h"
#include "SynCondition.h"
#include "TcpOptionCondition.h"
#include "TosCondition.h"
#include "TtlEqCondition.h"
#include "TtlGtCondition.h"
#include "TtlLtCondition.h"
#include "DscpCondition.h"
#include "IcmpTypeCondition.h"
#include "SrcTypeCondition.h"
#include "DstTypeCondition.h"
#include "StateCondition.h"
#include "CtorigdstCondition.h"

/**
 * Initialization of static members.
 */
ConditionFactory* ConditionFactory::fInstance = 0;

/**
 * Supported iptables conditions
 */
const std::string PROTOCOL = "-p";
const std::string PROTOCOL_ALIAS = "--protocol";
const std::string SRC_IP = "-s";
const std::string SRC_IP_ALIAS = "--source";
const std::string SRC_PORT = "--sport";
const std::string SRC_PORT_ALIAS = "--source-port";
const std::string DST_IP = "-d";
const std::string DST_IP_ALIAS = "--destination";
const std::string DST_PORT = "--dport";
const std::string DST_PORT_ALIAS = "--destination-port";
const std::string MODULE = "-m";
const std::string MODULE_ALIAS = "--match";
const std::string DST_PORTS = "--dports";
const std::string DST_PORTS_ALIAS = "--destination-ports";
const std::string SRC_PORTS = "--sports";
const std::string SRC_PORTS_ALIAS = "--source-ports";
const std::string PORTS = "--ports";
const std::string IN_INTERFACE = "-i";
const std::string IN_INTERFACE_ALIAS = "--in-interface";
const std::string OUT_INTERFACE = "-o";
const std::string OUT_INTERFACE_ALIAS = "--out-interface";
const std::string TCP_FLAGS = "--tcp-flags";
const std::string SYN = "--syn";
const std::string TCP_OPTION = "--tcp-option";
const std::string TOS = "--tos";
const std::string TTLEQ = "--ttl-eq";
const std::string TTLGT = "--ttl-gt";
const std::string TTLLT	= "--ttl-lt";
const std::string DSCP = "--dscp";
const std::string ICMPTYPE = "--icmp-type";
const std::string SRC_TYPE = "--src-type";
const std::string DST_TYPE = "--dst-type";
const std::string STATE = "--state";
const std::string CTORIGDST = "--ctorigdst";

ConditionFactory::ConditionFactory(NetworkLayout* networkLayout) : _networkLayout(networkLayout) {
	_parameterMap[PROTOCOL] = 1;
	_parameterMap[PROTOCOL_ALIAS] = 1;
	_parameterMap[SRC_IP] = 1;
	_parameterMap[SRC_IP_ALIAS] = 1;
	_parameterMap[SRC_PORT] = 1;
	_parameterMap[SRC_PORT_ALIAS] = 1;
	_parameterMap[DST_IP] = 1;
	_parameterMap[DST_IP_ALIAS] = 1;
	_parameterMap[DST_PORT] = 1;
	_parameterMap[DST_PORT_ALIAS] = 1;
	_parameterMap[MODULE] = 1;
	_parameterMap[MODULE_ALIAS] = 1;
	_parameterMap[DST_PORTS] = 1;
	_parameterMap[DST_PORTS_ALIAS] = 1;
	_parameterMap[SRC_PORTS] = 1;
	_parameterMap[SRC_PORTS_ALIAS] = 1;
	_parameterMap[PORTS] = 1;
	_parameterMap[IN_INTERFACE] = 1;
	_parameterMap[IN_INTERFACE_ALIAS] = 1;
	_parameterMap[OUT_INTERFACE] = 1;
	_parameterMap[OUT_INTERFACE_ALIAS] = 1;
	_parameterMap[TCP_FLAGS] = 2;
	_parameterMap[SYN] = 0;
	_parameterMap[TCP_OPTION] = 1;
	_parameterMap[TOS] = 1;
	_parameterMap[TTLEQ] = 1;
	_parameterMap[TTLGT] = 1;
	_parameterMap[TTLLT] = 1;
	_parameterMap[DSCP] = 1;
	_parameterMap[ICMPTYPE] = 1;
	_parameterMap[SRC_TYPE] = 1;
	_parameterMap[DST_TYPE] = 1;
	_parameterMap[STATE] = 1;
	_parameterMap[CTORIGDST] = 1;
}

ConditionFactory* ConditionFactory::getInstance(NetworkLayout* networkLayout) {
	if (fInstance == 0) {
		//create the 1 instance of the object (singleton)
		fInstance = new ConditionFactory(networkLayout);
	}
	return fInstance;
}

Condition* ConditionFactory::parseCondition(std::string name, std::vector<std::string> values, bool reverse) {
	Condition* cond = 0;
	if (name == PROTOCOL) {
		cond = new ProtocolCondition(values[0], reverse);
	} else if ((name == SRC_IP) || (name == SRC_IP_ALIAS)) {
		cond = new SourceCondition(values[0], reverse);
	} else if ((name == SRC_PORT) || (name == SRC_PORT_ALIAS)) {
		cond = new SrcPortCondition(values[0], reverse);
	} else if ((name == DST_IP) || (name == DST_IP_ALIAS)) {
		cond = new DestinationCondition(values[0], reverse);
	} else if ((name == DST_PORT) || (name == DST_PORT_ALIAS)) {
		cond = new DstPortCondition(values[0], reverse);
	} else if ((name == DST_PORTS) || (name == DST_PORTS_ALIAS)) {
		cond = new DstPortsCondition(values[0], reverse);
	} else if ((name == SRC_PORTS) || (name == SRC_PORTS_ALIAS)) {
		cond = new SrcPortsCondition(values[0], reverse);
	} else if (name == PORTS) {
		cond = new PortsCondition(values[0], reverse);
	} else if ((name == IN_INTERFACE) || (name == IN_INTERFACE_ALIAS)) {
		cond = new InInterfaceCondition(values[0], _networkLayout, reverse);
	} else if ((name == OUT_INTERFACE) || (name == OUT_INTERFACE_ALIAS)) {
		cond = new OutInterfaceCondition(values[0], _networkLayout, reverse);
	} else if (name == TCP_FLAGS) {
		cond = new TcpFlagsCondition(values[0], values[1], reverse);
	} else if (name == SYN) {
		cond = new SynCondition(reverse);
	} else if (name == TCP_OPTION) {
		cond = new TcpOptionCondition(values[0], reverse);
	} else if (name == TOS) {
		assert(!reverse);
		cond = new TosCondition(values[0]);
	} else if (name == TTLEQ) {
		assert(!reverse);
		cond = new TtlEqCondition(values[0]);
	} else if (name == TTLGT) {
		assert(!reverse);
		cond = new TtlGtCondition(values[0]);
	} else if (name == TTLLT) {
		assert(!reverse);
		cond = new TtlLtCondition(values[0]);
	} else if (name == DSCP) {
		assert(!reverse);
		cond = new DscpCondition(values[0]);
	} else if (name == ICMPTYPE) {
		cond = new IcmpTypeCondition(values[0], reverse);
	} else if (name == SRC_TYPE) {
		cond = new SrcTypeCondition(values[0], _networkLayout);
	} else if (name == DST_TYPE) {
		cond = new DstTypeCondition(values[0], _networkLayout);
	} else if (name == STATE) {
		cond = new StateCondition(values[0]);
	} else if (name == CTORIGDST) {
		cond = new CtorigdstCondition(values[0]);
	} else if ((name == MODULE) || (name == MODULE_ALIAS)) {
		//Ignore this condition
		return 0;
	} else {
		Poco::Logger::get("ConsoleLogger").debug("Combination Condition name = " + name + " and value(s) ");
		for(std::vector<std::string>::iterator it = values.begin(); it != values.end(); it++){
			std::cout << *it << " ";
		}
		std::cout << "is not tolerated. Terminating." << std::endl;
		exit(1);
	}
	return cond;
}

std::vector<Condition*> ConditionFactory::parse(std::vector<std::string> conditionList) {
	std::vector<Condition*> result;
	int nrOfParameters = 1;
	for(std::vector<std::string>::iterator it = conditionList.begin(); it != conditionList.end();it+=(nrOfParameters+1)){
		bool reverse = false;

		// some conditions are preceded with "!"
		if (*it == "!") {
			reverse = true;
			it++;
		}

		std::string name = *it;

		// some conditions are followed with "!"
		if ((it+1 != conditionList.end()) && (*(it+1) == "!")) {
			reverse = true;
			it++;
		}

		nrOfParameters = _parameterMap[name];
		std::vector<std::string> values;
		for(int index = 1; index <= nrOfParameters; index++){
			Poco::Logger::get("ConsoleLogger").debug("condition " + name + " value" + itoa(index) + " = " + *(it+index));
			values.push_back(*(it+index));
		}
		Condition* cond = this->parseCondition(name, values, reverse);
		if (cond) {
			result.push_back(cond);
		}
	}
	return result;
}
