/**
 * @file ScriptResolver.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <fstream>
#include <stdlib.h>
#include "assert.h"
#include <iostream>
#include <sstream>

//Poco
#include "Poco/Logger.h"

//FireSim
#include "ScriptResolver.h"
#include "../../ApplicationConstants.h"

std::string ScriptResolver::resolve(std::string config_path){
	Poco::Logger::get("ConsoleLogger").debug("script resolving...");
	//Set up temporary output
	std::ofstream script;
	script.open("script_resolver.sh");
	//include general variables specific for a certain firewall.
	script << ". " << config_path << SCRIPT_VARS_FILENAME << std::endl;
	script << "exec 3<> script_resolved.txt" << std::endl;
	script << _script << std::endl;
	script << "exec 3>&-" << std::endl;
	script.close();

	//Run script
	if (system("sh script_resolver.sh")){
		std::cout << "ScriptResolver: System call \"sh script_resolver.sh\" failed." << std::endl;
		exit(1);
	}
	std::string line;
	std::ifstream resolved;
	resolved.open("script_resolved.txt");
	assert(resolved.is_open());
	std::stringstream sstream;
	while (!resolved.eof() )
	{
		std::getline (resolved,line);
		sstream << line << std::endl;
	}
	resolved.close();

	if (system("rm script_resolved.txt")){
		std::cout << "ScriptResolver: System call \"rm script_resolved.txt\" failed." << std::endl;
		exit(1);
	}
	if (system("rm script_resolver.sh")){
		std::cout << "ScriptResolver: System call \"rm script_resolver.sh\" failed." << std::endl;
		exit(1);
	}
	return sstream.str();
}
