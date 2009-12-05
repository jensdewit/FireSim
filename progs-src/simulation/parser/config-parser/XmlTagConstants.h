/**
 * @file XmlTagConstants.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef XMLTAGCONSTANTS_H_
#define XMLTAGCONSTANTS_H_

#include <string>

/**
 * XMLConstants; tags used in our xml
 */
struct XMLConstants {
	static const std::string CONFIG_TAG;
	static const std::string TRAFFIC_TAG;
	static const std::string SOURCE_IP_TAG;
	static const std::string SOURCE_PORT_TAG;
	static const std::string DESTINATION_IP_TAG;
	static const std::string DESTINATION_PORT_TAG;
	static const std::string PROTOCOL_TAG;
	static const std::string TCP_FLAGS_TAG;
	static const std::string URG_FLAG_TAG;
	static const std::string ACK_FLAG_TAG;
	static const std::string PSH_FLAG_TAG;
	static const std::string RST_FLAG_TAG;
	static const std::string SYN_FLAG_TAG;
	static const std::string FIN_FLAG_TAG;
	static const std::string ICMP_TYPE;
	static const std::string ICMP_CODE;
	static const std::string POLICY_TAG;
	static const std::string IN_INTERFACE_TAG;
	static const std::string OUT_INTERFACE_TAG;
	static const std::string DUMP_TAG;
};

#endif /* XMLTAGCONSTANTS_H_ */

