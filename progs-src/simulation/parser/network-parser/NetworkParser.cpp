/**
 * @file ConfigParser.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <stdlib.h>
#include <iostream>
#include "assert.h"

//Poco
#include "Poco/DOM/Node.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/Exception.h"

//Firesim
#include "NetworkParser.h"
#include "XmlTagConstants.h"

using Poco::XML::Node;
using Poco::XML::NamedNodeMap;

/**
 * Initialization of static members.
 */
NetworkParser* NetworkParser::fInstance = 0;

NetworkParser::NetworkParser() {
}

NetworkParser* NetworkParser::getInstance() {
	if (fInstance == 0) {
		//create the 1 instance of the object (singleton)
		fInstance = new NetworkParser();
	}
	return fInstance;
}

NetworkLayout* NetworkParser::parse(Poco::XML::Document* xmlDocument) {
	//TODO Check whether is valid xml to construct a {@link PutContent}. XML Schema needed?

	Node* networkNode = xmlDocument->firstChild();
	assert(networkNode && (networkNode->nodeName()==XMLConstants::NETWORK_LAYOUT_TAG));

	NetworkLayout* layout = new NetworkLayout();

	Node* interfaceNode = networkNode->firstChild();
	while (interfaceNode != 0) {
		assert(interfaceNode->nodeName() == XMLConstants::INTERFACE_TAG);

		NetworkContent* content = new NetworkContent();
		content->mac_address = "00:00:00:00:00:00";

		NamedNodeMap* attributes = interfaceNode->attributes();
		assert(attributes->length() == 1);

		Node* status = attributes->getNamedItem(XMLConstants::STATUS_TAG);
		assert(status);
		content->status = status->nodeValue();

		attributes->release();

		Node* elementNode = interfaceNode->firstChild();
		while (elementNode != 0){
			//elementNode must be an element node with name NAME_TAG, MAC_ADDRESS_TAG or IP_ADDRESS_TAG
			assert((elementNode->nodeName()==XMLConstants::NAME_TAG)
					|| (elementNode->nodeName()==XMLConstants::MAC_ADDRESS_TAG)
					|| (elementNode->nodeName()==XMLConstants::IP_ADDRESS_TAG)
					|| (elementNode->nodeName()==XMLConstants::MASK_TAG)
					|| (elementNode->nodeName()==XMLConstants::BROADCAST_TAG));

			Node* textNode = elementNode->firstChild();

			if (textNode) {
				if (elementNode->nodeName() == XMLConstants::NAME_TAG) {
					content->name = textNode->nodeValue();
				} else if (elementNode->nodeName() == XMLConstants::MAC_ADDRESS_TAG){
					content->mac_address = textNode->nodeValue();
				} else if (elementNode->nodeName() == XMLConstants::IP_ADDRESS_TAG) {
					try {
						content->ip_address = IPAddress(textNode->nodeValue());
					} catch (Poco::Exception e) {
						std::cout << "Parsed faulty IP address: '" << e.message() << "'. Terminating." << std::endl;
						exit(1);
					}
				} else if (elementNode->nodeName() == XMLConstants::MASK_TAG) {
					try {
						content->mask = IPAddress(textNode->nodeValue());
					} catch (Poco::Exception e) {
						std::cout << "Parsed faulty IP mask: '" << e.message() << "'. Terminating." << std::endl;
						exit(1);
					}
				} else if (elementNode->nodeName() == XMLConstants::BROADCAST_TAG) {
					try {
						content->broadcast = IPAddress(textNode->nodeValue());
					} catch (Poco::Exception e) {
						std::cout << "Parsed faulty broadcast address: '" << e.message() << "'. Terminating." << std::endl;
						exit(1);
					}
				}
			}

			elementNode = elementNode->nextSibling();
		}

		layout->add(content);

		interfaceNode = interfaceNode->nextSibling();
	}

	return layout;
}
