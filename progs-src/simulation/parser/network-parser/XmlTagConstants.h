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
	static const std::string NETWORK_LAYOUT_TAG;
	static const std::string INTERFACE_TAG;
	static const std::string NAME_TAG;
	static const std::string IP_ADDRESS_TAG;
	static const std::string MAC_ADDRESS_TAG;
	static const std::string MASK_TAG;
	static const std::string BROADCAST_TAG;
	static const std::string STATUS_TAG;
};

#endif /* XMLTAGCONSTANTS_H_ */

