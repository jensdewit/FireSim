/**
 * @file Main.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <iostream>
#include <sstream>
#include <fstream>

//Logger
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/SplitterChannel.h"
#include "Poco/Message.h"

//Threading
#include "Poco/Thread.h"

//Poco
#include "Poco/StringTokenizer.h"

//FireSim
#include "StartClick.h"
#include "ApplicationConstants.h"
#include "statistics/Statistics.h"
#include "clickgenerator/ClickGenerator.h"
#include "util/Util.h"

using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::SplitterChannel;
using Poco::Message;

bool checkFile(std::string path){
	//shorewall.compiled
	std::ifstream check;
	check.open(path.c_str());
	return check.is_open();
	check.close();
}

/**
 * Main method of FireSim
 */
int main(int argc, char **argv) {
	removeFiles(read_directory(OUTPUT_PATH), OUTPUT_PATH);

	//Initialize logging system
	// set up channel chains
	FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("%t"));
	SplitterChannel* splitter = new SplitterChannel();
	splitter->addChannel(new ConsoleChannel);
//	FileChannel* logFileChannel = new FileChannel("firesim.log");
//	splitter->addChannel(logFileChannel);
	pFCConsole->setChannel(splitter);
	pFCConsole->open();

//	FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%d-%m-%Y %H:%M:%S.%c %N[processID %P]: %p: %t"));
//	pFCFile->setChannel(logFileChannel);
//	pFCFile->open();

	//Message priorities: Fatal, Critical, Error, Warning, Notice, Information, Debug, Trace
	// create two Logger objects - one for
	// each channel chain.
	Logger::create("ConsoleLogger", pFCConsole, Message::PRIO_INFORMATION);
//	Logger::create("FileLogger", pFCFile, Message::PRIO_ERROR);

	//print ascii-logo
	std::stringstream stringstream;
	printFireSimLogo(stringstream);
	Logger::get("ConsoleLogger").information(stringstream.str());

	//Check whether required input files are present in config folder
	Logger::get("ConsoleLogger").information("Required input files:");
	//shorewall.compiled
	Poco::StringTokenizer shorewallCompiledTokenizer(CONFIG_PATH + SHOREWALLCOMPILED_FILENAME, "/", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if (checkFile(CONFIG_PATH + SHOREWALLCOMPILED_FILENAME)){
		Logger::get("ConsoleLogger").information(shorewallCompiledTokenizer[shorewallCompiledTokenizer.count()-1] + " is found in config folder.");
	} else {
		Logger::get("ConsoleLogger").information(shorewallCompiledTokenizer[shorewallCompiledTokenizer.count()-1] + " is not found in config folder. Shorewall can generate this file.");
		exit(1);
	}

	//config.xml
	Poco::StringTokenizer configTokenizer(CONFIG_PATH + CONFIG_FILENAME, "/", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if (checkFile(CONFIG_PATH + CONFIG_FILENAME)){
		Logger::get("ConsoleLogger").information(configTokenizer[configTokenizer.count()-1] + " is found in config folder.");
	} else {
		Logger::get("ConsoleLogger").information(configTokenizer[configTokenizer.count()-1] + " is not found in config folder. See README.txt for more info.");
		exit(1);
	}

	//network_layout.xml
	Poco::StringTokenizer networkLayoutTokenizer(CONFIG_PATH + NETWORKLAYOUT_FILENAME, "/", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if (checkFile(CONFIG_PATH + NETWORKLAYOUT_FILENAME)){
		Logger::get("ConsoleLogger").information(networkLayoutTokenizer[networkLayoutTokenizer.count()-1] + " is found in config folder.");
	} else {
		Logger::get("ConsoleLogger").information(networkLayoutTokenizer[networkLayoutTokenizer.count()-1] + " is not found in config folder. Run [$config]/firewall_config_extract.sh on your firewall. It will generate " + networkLayoutTokenizer[networkLayoutTokenizer.count()-1]);
		exit(1);
	}

	//script_vars.sh
	Poco::StringTokenizer scriptVarsTokenizer(CONFIG_PATH + SCRIPT_VARS_FILENAME, "/", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	if (checkFile(CONFIG_PATH + SCRIPT_VARS_FILENAME)){
		Logger::get("ConsoleLogger").information(scriptVarsTokenizer[scriptVarsTokenizer.count()-1] + " is found in config folder.");
	} else {
		Logger::get("ConsoleLogger").information(scriptVarsTokenizer[scriptVarsTokenizer.count()-1] + " is not found in config folder. Run [$config]/firewall_config_extract.sh on your firewall. It will generate " + scriptVarsTokenizer[scriptVarsTokenizer.count()-1]);
		exit(1);
	}
	Logger::get("ConsoleLogger").information("");

	//Set up output
	std::ofstream clickSimulationScript;
	clickSimulationScript.open((SCRIPT_DIR + SIMULATION_SCRIPT).c_str());
	std::ofstream clickTraceScript;
	clickTraceScript.open((SCRIPT_DIR + TRACE_SCRIPT).c_str());

	//Generate click script for simulation
	ClickGenerator clickGenerator;
	clickGenerator.generateSimulation(clickSimulationScript);
	clickSimulationScript.close();
	clickGenerator.generateTraces(clickTraceScript);
	clickTraceScript.close();

	//Start simulation
	Logger::get("ConsoleLogger").information("Simulate firewall with CLICK.");
	Logger::get("ConsoleLogger").information("");
	Poco::Thread* thread = new Poco::Thread();
	StartClick* clickSimulation = new StartClick(SIMULATION_SCRIPT, CLICK_PORT, " 1>/dev/null 2>/dev/null");
	thread->start(*clickSimulation);

	//Feedback to the user
	Statistics stats = Statistics();
	stats.getUserReport();

	//Stop simulation
	if (clickSimulation) {
		delete(clickSimulation);
	}

	Logger::get("ConsoleLogger").information("");

	//Do the traces the user requested
	stats.doTraces();

	Logger::get("ConsoleLogger").information("");
}
