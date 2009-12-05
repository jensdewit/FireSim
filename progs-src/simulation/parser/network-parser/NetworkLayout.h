/**
 * @file NetworkLayout.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef NETWORKLAYOUT_H_
#define NETWORKLAYOUT_H_

//Standard
#include <iostream>
#include <map>
#include <vector>
//Poco
//FireSim
#include "NetworkContent.h"

/**
 * @class NetworkLayout
 */
class NetworkLayout {
public:

	/**
	 * Default constructor.
	 */
	NetworkLayout();

	/**
	 * Destructor.
	 */
	~NetworkLayout();

	/**
	 * Add a network interface to the network layout.
	 */
	void add(NetworkContent*);

	/**
	 * Get all broadcast addresses
	 */
	std::vector<std::string> getBroadcastAddresses();

	/**
	 * Get all MAC addresses and their matching IP addresses
	 */
	std::map<std::string, std::string> getMacIPMappings();

	/**
	 * Check whether the specified interface exists.
	 */
	bool hasInterface(std::string interface);

	/**
	 * Search the MAC address of a network interface
	 */
	std::string getMacAddress(std::string interface);

	/**
	 * Search the IP address of a network interface
	 */
	std::string getIpAddress(std::string interface);

	/**
	 * Is it firewall internal traffic
	 */
	bool isInternal(std::string srcIP, std::string dstIP);

	/**
	 * Is it firewall output?
	 */
	bool isOutput(std::string srcIP);

	/**
	 * Is it firewall input?
	 */
	bool isInput(std::string dstIP);

	/**
	 * Print click startchain switch
	 * @param ostream This is the output stream. The startchain switch will be printed to this stream.
	 * @param elementName This is the name of the click switch element.
	 */
	void printStartChainSwitch(std::ostream& ostream, std::string elementName);

	/**
	 * Print click masquerade switch
	 * @param ostream This is the output stream. The masquerade switch will be printed to this stream.
	 */
	void printMasqueradeSwitch(std::ostream& ostream);

private:
	bool find(std::string ip);
	std::map<std::string, NetworkContent*> _content;
};

#endif /* NETWORKLAYOUT_H_ */
