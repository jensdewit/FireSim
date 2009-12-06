/**
 * @file ClickGenerator.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <iostream>
#include "assert.h"

//Poco
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/SAX/SAXException.h"
#include "Poco/Exception.h"

//FireSim
#include "ClickGenerator.h"
#include "../parser/shorewall-parser/ShorewallParser.h"
#include "../parser/config-parser/ConfigParser.h"
#include "../parser/network-parser/NetworkParser.h"
#include "../ApplicationConstants.h"

ClickGenerator::ClickGenerator() {
	_filterTable = 0;
	_natTable = 0;
	_mangleTable = 0;
	_networkLayout = 0;
}

ClickGenerator::~ClickGenerator() {
	if (_filterTable) {
		delete _filterTable;
	}
	if (_natTable) {
		delete _natTable;
	}
}
void ClickGenerator::generateSimulation(std::ostream& output, std::string config_path) {
	Poco::XML::DOMParser DOMparser;

	//Parse network layout
	try {
		//Skip whitespace
		DOMparser.setFeature("http://www.appinf.com/features/no-whitespace-in-element-content", false);
		Poco::XML::Document* xmlDoc = DOMparser.parse(config_path + NETWORKLAYOUT_FILENAME);
		NetworkParser* networkParser = NetworkParser::getInstance();
		_networkLayout = networkParser->parse(xmlDoc);
	} catch (Poco::XML::SAXParseException e){
		std::cout << "Failure while parsing network_layout.xml file at line " << e.getLineNumber() << " and column " << e.getColumnNumber() << ": " << e.name() << std::endl;
		exit(1);
	}
	//Parse shorewall compiled
	ShorewallParser::createInstance(config_path, _networkLayout);
	ShorewallParser* parser = ShorewallParser::getInstance();
	_filterTable = parser->parseFilterTable();
	_natTable = parser->parseNatTable();
	_mangleTable = parser->parseMangleTable();

	ConfigParser* configParser = 0;
	try {
		//Parse configuration
		Poco::XML::Document* xmlDoc2 = DOMparser.parse(config_path + CONFIG_FILENAME);
		ConfigParser::createInstance(config_path);
		configParser = ConfigParser::getInstance();
		configParser->parse(xmlDoc2, _networkLayout);
	} catch (Poco::XML::SAXParseException e){
		std::cout << "Failure while parsing config.xml file at line " << e.getLineNumber() << " and column " << e.getColumnNumber() << ": " << e.name() << std::endl;
		exit(1);
	}

	//Generate click script
	output << "//Please don't alter the content of this generated file by FireSim" << std::endl;
	output << "//authors: Nico Van Looy & Jens De Wit - 2009" << std::endl;
	output << std::endl;

	output << "//Translation of iptables to click syntax" << std::endl;
	_mangleTable->printClickClassifiers(output, "MANGLE_");
	_natTable->printClickClassifiers(output, "NAT_");
	_filterTable->printClickClassifiers(output, "FILTER_");
	output << std::endl;

	output << "//Painters for statistics" << std::endl;
	output << "Idle -> ACCEPT_CHECK :: CheckPaint(COLOR 0);" << std::endl;
	output << "Idle -> REJECT :: CheckPaint(COLOR 1);" << std::endl;
	output << "Idle -> DROP :: CheckPaint(COLOR 2);" << std::endl;
	output << std::endl;

	output << "//Link tables" << std::endl;
	output
			<< "ACCEPT :: TableLinker(ACCEPT ACCEPT_CHECK, MANGLE_PREROUTING MANGLE_PREROUTING1, MANGLE_INPUT MANGLE_INPUT1, MANGLE_FORWARD MANGLE_FORWARD1, MANGLE_OUTPUT MANGLE_OUTPUT1, MANGLE_POSTROUTING MANGLE_POSTROUTING1, NAT_PREROUTING NAT_PREROUTING1, NAT_POSTROUTING NAT_POSTROUTING1, NAT_OUTPUT NAT_OUTPUT1, FILTER_INPUT FILTER_INPUT1, FILTER_FORWARD FILTER_FORWARD1, FILTER_OUTPUT FILTER_OUTPUT1);"
			<< std::endl;
	output << std::endl;

	output << "//Intern - input - forward - output iptables switch" << std::endl;
	_networkLayout->printStartChainSwitch(output, "IPTABLES");
	output << "IPTABLES[0] -> Script(TYPE PACKET, write ACCEPT.chain \"INTERN\") -> MANGLE_OUTPUT1; //Internal traffic" << std::endl; //Internal Traffic
	output << "IPTABLES[1] -> Script(TYPE PACKET, write ACCEPT.chain \"OUTPUT\") -> MANGLE_OUTPUT1; //Output Chain" << std::endl; //Output Chain
	output << "IPTABLES[2] -> Script(TYPE PACKET, write ACCEPT.chain \"INPUT\") -> MANGLE_PREROUTING1; //Input Chain" << std::endl; //Input Chain
	output << "IPTABLES[3] -> Script(TYPE PACKET, write ACCEPT.chain \"FORWARD\") -> MANGLE_PREROUTING1; //Forward Chain" << std::endl; //Forward Chain
	output << std::endl;

	output << "//Counters for statistics" << std::endl;
	output << "inputCounter :: Counter -> IPTABLES;" << std::endl;
	output << "ACCEPT_true :: Counter;" << std::endl;
	output << "ACCEPT_false :: Counter;" << std::endl;
	output << "REJECT_true :: Counter;" << std::endl;
	output << "REJECT_false :: Counter;" << std::endl;
	output << "DROP_true :: Counter;" << std::endl;
	output << "DROP_false :: Counter;" << std::endl;
	output << std::endl;

//	output << "//Traffic queue" << std::endl;
//	output << "queue :: SimpleQueue" << std::endl;
//	output << "	-> unqueue :: PokeUnqueue" << std::endl;
//	output << "	-> Script(TYPE PACKET, write bt.reset)" << std::endl;

	output << "//Traffic copy" << std::endl;
	output << "copy :: Tee;" << std::endl;
	output << std::endl;

	output << "//Traffic input queue" << std::endl;
	output << "queue :: SimpleQueue" << std::endl;
	output << "	-> unqueue :: PokeUnqueue" << std::endl;
	output << "	-> copy;" << std::endl;
	output << std::endl;

	output << "//Faulty accept output queue" << std::endl;
	output << "copy[0] -> faulty_accept_queue :: SimpleQueue" << std::endl;
	output << "	-> faulty_accept :: PokeUnqueue" << std::endl;
	output << "	-> ToDump(\"" << OUTPUT_PATH << "faulty_accept.dump\");" << std::endl;
	output << std::endl;

	output << "//Faulty reject output queue" << std::endl;
	output << "copy[1] -> faulty_reject_queue :: SimpleQueue" << std::endl;
	output << "	-> faulty_reject :: PokeUnqueue" << std::endl;
	output << "	-> ToDump(\"" << OUTPUT_PATH << "faulty_reject.dump\");" << std::endl;
	output << std::endl;

	output << "//Faulty drop output queue" << std::endl;
	output << "copy[2] -> faulty_drop_queue :: SimpleQueue" << std::endl;
	output << "	-> faulty_drop :: PokeUnqueue" << std::endl;
	output << "	-> ToDump(\"" << OUTPUT_PATH << "faulty_drop.dump\");" << std::endl;
	output << std::endl;

	output << "//Do simulation with input traffic" << std::endl;
	output << "copy[3] -> Script(TYPE PACKET, write bt.reset)" << std::endl;
	output << "	-> MarkIPHeader(14)" << std::endl;
	output << "	-> inputCounter;" << std::endl;
	output << std::endl;

	output << "//Clear the output queues and get the next input packet going" << std::endl;
	output << "	next :: Script(TYPE PACKET, write faulty_accept_queue.reset)" << std::endl;
	output << "	-> Script(TYPE PACKET, write faulty_reject_queue.reset)" << std::endl;
	output << "	-> Script(TYPE PACKET, write faulty_drop_queue.reset)" << std::endl;
	output << "	-> Script(TYPE PACKET, write unqueue.poke) -> Discard;" << std::endl;
	output << std::endl;

	output << "//Feedback" << std::endl;
	output << "ACCEPT_CHECK[0] -> ACCEPT_true -> next" << std::endl;
	output << "ACCEPT_CHECK[1] -> ACCEPT_false -> Script(TYPE PACKET, write faulty_accept.poke) -> next" << std::endl;
	output << "REJECT[0] -> REJECT_true -> next" << std::endl;
	output << "REJECT[1] -> REJECT_false -> Script(TYPE PACKET, write faulty_reject.poke) -> next" << std::endl;
	output << "DROP[0] -> DROP_true -> next" << std::endl;
	output << "DROP[1] -> DROP_false -> Script(TYPE PACKET, write faulty_drop.poke) -> next" << std::endl;
	output << std::endl;

	output << "Idle -> MANGLE_INPUT1;" << std::endl;
	output << "Idle -> MANGLE_FORWARD1;" << std::endl;
	output << "Idle -> MANGLE_POSTROUTING1;" << std::endl;
	output << "Idle -> NAT_OUTPUT1;" << std::endl;
	output << "Idle -> NAT_PREROUTING1;" << std::endl;
	output << "Idle -> NAT_POSTROUTING1;" << std::endl;
	output << "Idle -> FILTER_FORWARD1;" << std::endl;
	output << "Idle -> FILTER_INPUT1;" << std::endl;
	output << "Idle -> FILTER_OUTPUT1;" << std::endl;
	output << "Idle -> ACCEPT_CHECK;" << std::endl;
	output << std::endl;

	output << "//Backtracker declaration" << std::endl;
	output << "Idle -> bt :: Backtracker;" << std::endl;
	output << std::endl;

	_networkLayout->printMasqueradeSwitch(output);

	configParser->printClickTraffic(output, _networkLayout);

	output << "//Poke unqueue to start automatically" << std::endl;
	output << "Script(write unqueue.poke);" << std::endl;
	output << std::endl;

	output << "//Simulation of the iptables" << std::endl;
	_mangleTable->printClickSimulation(output, "MANGLE_");
	_natTable->printClickSimulation(output, "NAT_");
	_filterTable->printClickSimulation(output, "FILTER_");
}

void ClickGenerator::generateTraces(std::ostream& output) {
	assert(_filterTable);
	assert(_natTable);
	assert(_mangleTable);

	output << "//Please don't alter the content of this generated file by FireSim" << std::endl;
	output << "//authors: Nico Van Looy & Jens De Wit - 2009" << std::endl;
	output << std::endl;

	output << "//Translation of iptables to click syntax" << std::endl;
	_mangleTable->printClickClassifiers(output, "MANGLE_");
	_natTable->printClickClassifiers(output, "NAT_");
	_filterTable->printClickClassifiers(output, "FILTER_");
	output << std::endl;

	output << "//Pretty printers" << std::endl;
	_mangleTable->printPrettyPrinters(output, "MANGLE_");
	_natTable->printPrettyPrinters(output, "NAT_");
	_filterTable->printPrettyPrinters(output, "FILTER_");
	output << std::endl;

	output << "//Intern - input - forward - output iptables switch" << std::endl;
	_networkLayout->printStartChainSwitch(output, "IPTABLES");
	output << "IPTABLES[0] -> Script(TYPE PACKET, write ACCEPT.chain \"INTERN\") //Internal traffic" << std::endl; //Internal Traffic
	output << "	-> Script(TYPE PACKET, print \"This packet is classified as INTERNAL traffic.\")" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"Start -> MANGLE Table (Output Chain)\")" << std::endl;
	output << "	-> MANGLE_OUTPUT1Print;" << std::endl; //Internal Traffic

	output << "IPTABLES[1] -> Script(TYPE PACKET, write ACCEPT.chain \"OUTPUT\") //Output Chain" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"This packet is classified as OUTPUT.\")" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"Start -> MANGLE Table (Output Chain)\")" << std::endl;
	output << "	-> MANGLE_OUTPUT1Print;" << std::endl; //Output Chain

	output << "IPTABLES[2] -> Script(TYPE PACKET, write ACCEPT.chain \"INPUT\") //Input Chain" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"This packet is classified as INPUT.\")" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"Start -> MANGLE Table (Prerouting Chain)\")" << std::endl;
	output << "	-> MANGLE_PREROUTING1Print;" << std::endl; //Input Chain

	output << "IPTABLES[3] -> Script(TYPE PACKET, write ACCEPT.chain \"FORWARD\") //Forward Chain" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"This packet is classified as FORWARD.\")" << std::endl;
	output << "	-> Script(TYPE PACKET, print \"Start -> MANGLE Table (Prerouting Chain)\")" << std::endl;
	output << "	-> MANGLE_PREROUTING1Print;" << std::endl; //Forward Chain
	output << std::endl;

	output << "//Backtracker declaration" << std::endl;
	output << "Idle -> bt :: Backtracker;" << std::endl;
	output << std::endl;

	_networkLayout->printMasqueradeSwitch(output);

	output << "// Replay specific dump file" << std::endl;
	output << "FromDump($FILENAME)" << std::endl;
	output << "	-> SimpleQueue" << std::endl;
	output << "	-> unqueue :: PokeUnqueue" << std::endl;
	output << "	-> Script(TYPE PACKET, write bt.reset)" << std::endl;
	output << "	-> MarkIPHeader(14)" << std::endl;
	output << "	-> poke_counter :: Counter" << std::endl;
	output << "	-> Script(TYPE PACKET," << std::endl;
	output << "		set packetnr $(poke_counter.count)," << std::endl;
	output << "		print \"\nPacket\" $packetnr)" << std::endl;
	output << "	-> IPTABLES;" << std::endl;
	output << std::endl;

	output << "//Poke unqueue to start automatically" << std::endl;
	output << "Script(write unqueue.poke);" << std::endl;
	output << std::endl;

	output << "//Link tables" << std::endl;
	output << "Idle -> ACCEPT_CHECK :: Script(TYPE PACKET, write unqueue.poke) -> Discard;" << std::endl;
	output << "Idle -> ACCEPT :: TableLinker(ACCEPT ACCEPT_CHECK, MANGLE_PREROUTING MANGLE_PREROUTING1Print, MANGLE_INPUT MANGLE_INPUT1Print, MANGLE_FORWARD MANGLE_FORWARD1Print, MANGLE_OUTPUT MANGLE_OUTPUT1Print, MANGLE_POSTROUTING MANGLE_POSTROUTING1Print, NAT_PREROUTING NAT_PREROUTING1Print, NAT_POSTROUTING NAT_POSTROUTING1Print, NAT_OUTPUT NAT_OUTPUT1Print, FILTER_INPUT FILTER_INPUT1Print, FILTER_FORWARD FILTER_FORWARD1Print, FILTER_OUTPUT FILTER_OUTPUT1Print);" << std::endl;
	output << "Idle -> REJECT :: Script(TYPE PACKET, write unqueue.poke) -> Discard;" << std::endl;
	output << "Idle -> DROP :: Script(TYPE PACKET, write unqueue.poke) -> Discard;" << std::endl;
	output << std::endl;

	output << "Idle -> MANGLE_INPUT1Print;" << std::endl;
	output << "Idle -> MANGLE_FORWARD1Print;" << std::endl;
	output << "Idle -> MANGLE_POSTROUTING1Print;" << std::endl;
	output << "Idle -> NAT_OUTPUT1Print;" << std::endl;
	output << "Idle -> NAT_PREROUTING1Print;" << std::endl;
	output << "Idle -> NAT_POSTROUTING1Print;" << std::endl;
	output << "Idle -> FILTER_FORWARD1Print;" << std::endl;
	output << "Idle -> FILTER_INPUT1Print;" << std::endl;
	output << "Idle -> FILTER_OUTPUT1Print;" << std::endl;
	output << "Idle -> ACCEPT_CHECK;" << std::endl;
	output << std::endl;

	output << "//Simulation of the iptables" << std::endl;
	_mangleTable->printClickTraceSimulation(output, "MANGLE_");
	_natTable->printClickTraceSimulation(output, "NAT_");
	_filterTable->printClickTraceSimulation(output, "FILTER_");
	output << std::endl;
}
