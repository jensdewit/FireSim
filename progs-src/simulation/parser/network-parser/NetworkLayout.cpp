/**
 * @file NetworkLayout.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include "assert.h"
//Poco
#include "Poco/StringTokenizer.h"
//FireSim
#include "NetworkLayout.h"

NetworkLayout::NetworkLayout(){
}

NetworkLayout::~NetworkLayout() {
	for(std::map<std::string,NetworkContent*>::iterator it = _content.begin(); it != _content.end(); it++) {
		delete it->second;
	}
}

void NetworkLayout::add(NetworkContent* content){
	_content.insert(std::pair<std::string, NetworkContent*>(content->name, content));
}

std::vector<std::string> NetworkLayout::getBroadcastAddresses(){
	std::vector<std::string> broadcastAddresses;
	for(std::map<std::string, NetworkContent*>::iterator it = _content.begin(); it != _content.end();it++){
		if(it->second->broadcast.toString()!="0.0.0.0"){
			broadcastAddresses.push_back(it->second->broadcast.toString());
		}
	}
	return broadcastAddresses;
}

std::map<std::string,std::string> NetworkLayout::getMacIPMappings() {
	std::map<std::string, std::string> macIPMappings;
	for(std::map<std::string, NetworkContent*>::iterator it = _content.begin(); it != _content.end(); it++){
		macIPMappings[it->second->mac_address] = it->second->ip_address.toString();
//		// only take valid ip addresses into account
//		if (it->second->ip_address.toString() != "0.0.0.0") {
//			macIPMappings[it->second->mac_address] = it->second->ip_address.toString();
//		}
	}
	return macIPMappings;
}

bool NetworkLayout::hasInterface(std::string interface) {
	 if (_content.find(interface) == _content.end()) {
		 return false;
	 }
	 return true;
}

std::string NetworkLayout::getMacAddress(std::string interface) {
	assert(_content.find(interface) != _content.end());
	return _content[interface]->mac_address;
}

std::string NetworkLayout::getIpAddress(std::string interface){
	assert(_content.find(interface) != _content.end());
	return _content[interface]->ip_address.toString();
}

//helper function
bool NetworkLayout::find(std::string ip){
	bool found = false;
	std::map<std::string, std::string> network = getMacIPMappings();
	for(std::map<std::string, std::string>::iterator it = network.begin(); it != network.end();it++){
		if (it->second == ip){
			found = true;
			break;
		}
	}
	return found;
}

bool NetworkLayout::isInternal(std::string srcIP, std::string dstIP){
	return (find(srcIP) && find(dstIP));
}

bool NetworkLayout::isOutput(std::string srcIP){
	return find(srcIP);
}

bool NetworkLayout::isInput(std::string dstIP){
	return find(dstIP);
}

void NetworkLayout::printStartChainSwitch(std::ostream& ostream, std::string elementName){
	// Internal Traffic
	ostream << elementName << " :: IPClassifier(" << std::endl << "	(dst ";
	for(std::map<std::string, NetworkContent*>::iterator it = _content.begin(); it != _content.end();){
		ostream << it->second->ip_address.toString() << "/32";
		if ((++it) != _content.end()) {
			ostream << " or ";
		}
	}
	ostream << " ) and (src ";
	for(std::map<std::string, NetworkContent*>::iterator it = _content.begin(); it != _content.end();){
		ostream << it->second->ip_address.toString() << "/32";
		if ((++it) != _content.end()) {
			ostream << " or ";
		}
	}

	//ostream classification
	ostream << "), " << std::endl << "	src ";
	for(std::map<std::string, NetworkContent*>::iterator it = _content.begin(); it != _content.end();){
		ostream << it->second->ip_address.toString() << "/32";
		if ((++it) != _content.end()) {
			ostream << " or ";
		}
	}

	//Input classification
	ostream << ", " << std::endl << "	dst ";
	for(std::map<std::string, NetworkContent*>::iterator it = _content.begin(); it != _content.end();){
		ostream << it->second->ip_address.toString() << "/32";
		if ((++it) != _content.end()) {
			ostream << " or ";
		}
	}

	//Forward classification
	ostream << ", " << std::endl << "	-);" << std::endl;
}

void NetworkLayout::printMasqueradeSwitch(std::ostream& ostream) {
	ostream << "//Masquerade handler" << std::endl;
	std::map<std::string, std::string> mapping = this->getMacIPMappings();
	ostream << "Idle -> masq :: Classifier(";
	for(std::map<std::string, std::string>::iterator it = mapping.begin(); it != mapping.end();) {
		if (it->second != "0.0.0.0") {
			Poco::StringTokenizer macTokenizer(it->first, ":", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			ostream << "0/";
			for(int index = 0; index < macTokenizer.count(); index++){
				ostream << macTokenizer[index];
			}
			if ((++it) != mapping.end()) {
				ostream << ", ";
			}
		} else {
			it++;
		}

	}
	ostream << ");" << std::endl;
	int index = 0;
	for(std::map<std::string, std::string>::iterator it = mapping.begin(); it != mapping.end(); it++) {
		if (it->second != "0.0.0.0") {
			ostream << "masq[" << index << "] -> IPAddrPairRewriter(pattern " << it->second << " - 0 0) -> bt;" << std::endl;
			index++;
		}
	}
	ostream << std::endl;
}
