/**
 * @file Table.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#include "Table.h"
#include "assert.h"

Table::Table() {
	//Add standard targets
	this->add(new Chain("ACCEPT",true,true));
	this->add(new Chain("REJECT",true,true));
	this->add(new Chain("DROP",true,true));
	this->add(new Chain("RETURN",false));
	this->add(new Chain("ULOG",false));
	this->add(new Chain("DNAT",false));
	this->add(new Chain("SNAT",false));
	this->add(new Chain("MASQUERADE",false));
}

Table::~Table() {
	for(std::map<std::string,Chain*>::iterator it = _map.begin(); it != _map.end(); it++) {
		delete it->second;
	}
}

void Table::add(Chain* chain){
	_map.insert(std::pair<std::string, Chain*>(chain->getName(), chain));
}

Chain* Table::get(std::string name){
//	if (name[name.size()-1]=='\r'){
//		name =name.substr(0, name.size()-1);
//	}
//	for (int i = 0; i < name.size(); i++){
//		std::cout << "name[" << i << "] = " << name[i] << std::endl;
//	}
//	std::cout << "\0 = " << 'a' << std::endl;
//	std::cout << "get name = " << name << " (" << name.size() << " charachters)" << std::endl;
//	int index = 0;
//	for(std::map<std::string, Chain*>::iterator it = _map.begin(); it != _map.end(); it++){
//		std::cout << "map[" << index << "] = " << it->first << " (" << it->first.size() << " charachters)" << std::endl;
//		index++;
//	}
	assert((_map.find(name) != _map.end()));
	return _map.find(name)->second;
}

void Table::printClickClassifiers(std::ostream& ostream, std::string prefix){
	for(std::map<std::string, Chain*>::iterator it = _map.begin(); it != _map.end(); it++){
		if (!it->second->isFinal()){
			it->second->printClickClassifiers(ostream, prefix);
		}
	}
}

void Table::printClickSimulation(std::ostream& ostream, std::string prefix){
	for(std::map<std::string, Chain*>::iterator it = _map.begin(); it != _map.end(); it++){
		if (!it->second->isFinal()){
			it->second->printClickTraceSimulation(ostream, prefix);
		}
	}
}

void Table::printClickTraceSimulation(std::ostream& ostream, std::string prefix){
	for(std::map<std::string, Chain*>::iterator it = _map.begin(); it != _map.end(); it++){
		if (!it->second->isFinal()){
			it->second->printClickTraceSimulation(ostream, prefix, "Print");
		}
	}
}

void Table::printPrettyPrinters(std::ostream& ostream, std::string prefix){
	for(std::map<std::string, Chain*>::iterator it = _map.begin(); it != _map.end(); it++){
		if (!it->second->isFinal()){
			it->second->printPrettyPrinters(ostream, prefix);
		}
	}
}
