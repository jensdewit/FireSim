/**
 * @file ApplicationConstants.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef APPLICATIONCONSTANTS_H_
#define APPLICATIONCONSTANTS_H_

#include <string>

//Input files in config folder
const std::string CONFIG_PATH = std::string("../../config/");
const std::string SHOREWALLCOMPILED_FILENAME = std::string("shorewall.compiled");
const std::string CONFIG_FILENAME = std::string("config.xml");
const std::string NETWORKLAYOUT_FILENAME = std::string("network_layout.xml");
const std::string SCRIPT_VARS_FILENAME = "script_vars.sh";

//Output files
const std::string OUTPUT_PATH = "../../output/";

//Internal paths
const std::string CLICK_SHELL_CMD = "../../libs/Click/userlevel/click";

//Output click files
const std::string SCRIPT_DIR = "../../clickscripts/";
const std::string SIMULATION_SCRIPT = "firewall_simulation.click";
const std::string TRACE_SCRIPT = "rule_trace.click";

//Click port specification
const int CLICK_PORT = 10002;

#endif /* APPLICATIONCONSTANTS_H_ */
