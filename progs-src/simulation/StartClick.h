/**
 * @file StartClick.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef STARTCLICK_H_
#define STARTCLICK_H_

//Standard
#include <string>

//Poco
#include "Poco/Runnable.h"
#include "Poco/Logger.h"

//FireSim
#include "ApplicationConstants.h"
#include "util/Util.h"

/**
 * This is a runnable so we can run click in indepedent thread.
 */
class StartClick: public Poco::Runnable {
public:
	/**
	 * Constructor
	 */
	StartClick(std::string scriptName) {
		_scriptName = scriptName;
		_port = 0;
		_scriptParam = "";
	}

	/**
	 * Constructor
	 */
	StartClick(std::string scriptname, int port) {
		_scriptName = scriptname;
		_port = port;
		_scriptParam = "";
	}

	/**
	 * Constructor
	 */
	StartClick(std::string scriptname, int port, std::string scriptParam) {
		_scriptName = scriptname;
		_port = port;
		_scriptParam = scriptParam;
	}

	/**
	 * Destructor
	 */
	virtual ~StartClick(){
		//When this runnable is destructed, the click simulation must end.
		int status = system("pkill -SIGINT click");
		if (status == -1) {
			Poco::Logger::get("ConsoleLogger").critical("StartClick: shell command 'pkill -SIGINT click' has failed to execute. Please check your configuration.");
		}
	}

	/**
	 * Run click
	 */
	void run() {
		std::string shellCommand = CLICK_SHELL_CMD;
		if (_port != 0) {
			shellCommand += (" -p " + intToString(_port));
		}
		shellCommand += (" " + SCRIPT_DIR + _scriptName);
		if (_scriptParam != "") {
			shellCommand += (" " + _scriptParam);
		}
		if (system(shellCommand.c_str())){
			Poco::Logger::get("ConsoleLogger").critical("StartClick: shell command '" + shellCommand + "' has failed to execute. Please check your configuration.");
			exit(1);
		}
	}

private:
	std::string _scriptName;
	std::string _scriptParam;
	int _port;

};
#endif /* STARTCLICK_H_ */
