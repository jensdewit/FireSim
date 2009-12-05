/**
 * @file ClickGenerator.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef CLICKGENERATOR_H_
#define CLICKGENERATOR_H_

//Standard
//Poco
//FireSim
#include "../parser/shorewall-parser/Table.h"
#include "../parser/network-parser/NetworkLayout.h"


class ClickGenerator {
public:

	/**
	 * Default constructor
	 */
	ClickGenerator();

	/**
	 * Destructor
	 */
	~ClickGenerator();

	/**
	 * Generate a simulation click script, based on the current shorewall parser.
	 * @param output This is the output stream. The generated click script will be printed to this stream.
	 */
	void generateSimulation(std::ostream& output);

	/**
	 * Generate a trace click script for the last runned simulation, based on the current shorewall parser.
	 * @pre GenerateSimulation must once be called.
	 * @param output This is the output stream. The generated click script will be printed to this stream.
	 */
	void generateTraces(std::ostream& output);

private:
	Table* _filterTable;
	Table* _natTable;
	Table* _mangleTable;
	NetworkLayout* _networkLayout;
};
#endif /* CLICKGENERATOR_H_ */
