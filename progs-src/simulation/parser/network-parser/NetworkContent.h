/**
 * @file NetworkContent.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef NETWORKCONTENT_H_
#define NETWORKCONTENT_H_

//Standard
#include <string>

//Poco
#include "Poco/Net/IPAddress.h"

using Poco::Net::IPAddress;

/**
 * NetworkContent, containing name, MAC address and IP address of an interface.
 */
struct NetworkContent {
	std::string status;
	std::string name;
	std::string mac_address;
	IPAddress ip_address;
	IPAddress mask;
	IPAddress broadcast;

};

#endif /* NETWORKCONTENT_H_ */
