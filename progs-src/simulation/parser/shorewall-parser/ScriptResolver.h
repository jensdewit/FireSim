/**
 * @file ScriptResolver.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef SCRIPTRESOLVER_H_
#define SCRIPTRESOLVER_H_

//Standard
#include <string>
//Poco
//FireSim

class ScriptResolver {
public:

	/**
	 * Constructor
	 */
	ScriptResolver(std::string script) : _script(script) {
	}

	/**
	 * Run the script and return the output
	 * @param config_path The directory where the configuration files are located.
	 * @return scripts output
	 */
	std::string resolve(std::string config_path);

private:
	std::string _script;
};

#endif /* SCRIPTRESOLVER_H_ */
