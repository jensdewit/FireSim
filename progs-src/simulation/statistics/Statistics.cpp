/**
 * @file Statistics.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

//Logger
#include "Poco/Logger.h"

//Threading
#include "Poco/Thread.h"

//FireSim
#include "Statistics.h"
#include "CommandHandler.h"
#include "../StartClick.h"
#include "../ApplicationConstants.h"
#include "../util/Util.h"

using std::cout;
using std::endl;
using std::string;
using Poco::Logger;

Statistics::Statistics(){

}

Statistics::~Statistics(){

}

void Statistics::askForTrace(std::string filename, int captured) {
	Logger::get("ConsoleLogger").information("Do you want a trace for these packets? (y/n)");
	std::cout << "> ";
	std::cin.clear();
	std::string x;

	while(true) {
		getline(std::cin, x);
		if ((x != "y") && (x != "n") && (x != "Y") && (x != "N")
				&& (x != "yes") && (x != "no")) {
			Logger::get("ConsoleLogger").information("Wrong input. Do you want a trace for these packets? (y/n)");
		} else {
			break;
		}
	}

	if((x == "y") || (x == "yes") || (x == "Y")){
		//Add filename to pending traces
		_traceVector.push_back(std::pair<std::string, int> (filename, captured));
	}
}

void Statistics::doTraces() {
	for (std::vector<std::pair<std::string,int> >::const_iterator it = _traceVector.begin() ; it < _traceVector.end(); it++) {
		//first try to remove the .txt file because it may already exist from a previous run!
		remove((it->first + ".txt").c_str());

		Poco::Thread* thread = new Poco::Thread();
		StartClick* trace = new StartClick(TRACE_SCRIPT, CLICK_PORT,
				"FILENAME=" + OUTPUT_PATH + it->first + ".dump >> " + OUTPUT_PATH + it->first + ".txt 2>/dev/null");
		thread->start(*trace);

		CommandHandler cmdHandler("localhost", CLICK_PORT);
		while(true) {
			std::string clickReply = cmdHandler.execute("read poke_counter.count");
			if (stringToInt(clickReply) == it->second) {
				break;
			}
		}
		delete(trace);
		Logger::get("ConsoleLogger").information("Finished tracing " + it->first + ".dump: see " + it->first + ".txt in output folder");
	}
}

void Statistics::getUserReport() {
	CommandHandler cmdHandler("localhost", CLICK_PORT);

	//how many packets are generated?
	std::string clickReply = cmdHandler.execute("read inputCounter.count");
	Logger::get("ConsoleLogger").information("Total packets generated: " + clickReply);
	int totalNrOfPackets = stringToInt(clickReply);

	//how many packets are correctly accepted?
	clickReply = cmdHandler.execute("read ACCEPT_true.count");
	Logger::get("ConsoleLogger").information("Total packets correctly accepted: " + clickReply);
	int captured = stringToInt(clickReply);
	totalNrOfPackets -= captured; //for computation of total lost packets.

	//how many packets are incorrectly accepted?
	clickReply = cmdHandler.execute("read ACCEPT_false.count");
	captured = stringToInt(clickReply);
	std::string report = "Total packets incorrectly accepted: " + clickReply;
	if (captured > 0) {
		report += " (see faulty_accept.dump in output folder)";
		Logger::get("ConsoleLogger").information(report);
		askForTrace("faulty_accept", captured);
	} else {
		Logger::get("ConsoleLogger").information(report);
		removeFile("faulty_accept.dump", OUTPUT_PATH);
	}

	totalNrOfPackets -= captured; //for computation of total lost packets.

	//how many packets are correctly rejected?
	clickReply = cmdHandler.execute("read REJECT_true.count");
	Logger::get("ConsoleLogger").information("Total packets correctly rejected: " + clickReply);
	captured = stringToInt(clickReply);
	totalNrOfPackets -= captured; //for computation of total lost packets.

	//how many packets are incorrectly rejected?
	clickReply = cmdHandler.execute("read REJECT_false.count");
	captured = stringToInt(clickReply);
	report = "Total packets incorrectly rejected: " + clickReply;
	if (captured > 0) {
		report += " (see faulty_reject.dump in output folder)";
		Logger::get("ConsoleLogger").information(report);
		askForTrace("faulty_reject", captured);
	} else {
		Logger::get("ConsoleLogger").information(report);
		removeFile("faulty_reject.dump", OUTPUT_PATH);
	}
	totalNrOfPackets -= captured; //for computation of total lost packets.

	//how many packets are correctly dropped?
	clickReply = cmdHandler.execute("read DROP_true.count");
	Logger::get("ConsoleLogger").information("Total packets correctly dropped: " + clickReply);
	captured = stringToInt(clickReply);
	totalNrOfPackets -= captured; //for computation of total lost packets.

	//how many packets are incorrectly dropped?
	clickReply = cmdHandler.execute("read DROP_false.count");
	captured = stringToInt(clickReply);
	report = "Total packets incorrectly dropped: " + clickReply;
	if (captured > 0) {
		report += " (see faulty_drop.dump in output folder)";
		Logger::get("ConsoleLogger").information(report);
		askForTrace("faulty_drop", captured);
	} else {
		Logger::get("ConsoleLogger").information(report);
		removeFile("faulty_drop.dump", OUTPUT_PATH);
	}
	totalNrOfPackets -= captured; //for computation of total lost packets.

	std::string lost = intToString(totalNrOfPackets);

	//how many packets are lost?
	Logger::get("ConsoleLogger").information("Total packets lost: " + lost);

}
