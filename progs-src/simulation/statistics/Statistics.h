/**
 * @file Statistics.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

//Standard
#include <iostream>
#include <string>
#include <vector>

/**
 * {@class Statistics} is able to analyse the firewall simulation.
 */
class Statistics {
public:
	/**
	 * Constructor
	 */
	Statistics();

	/**
	 * Destructor
	 */
	virtual ~Statistics();

	/**
	 * Generate a status report of the firewall simulation.
	 * @param output is an outputstream for the report.
	 */
	void getUserReport();

	/**
	 * Generate a status report of the firewall simulation.
	 * @param output is an outputstream for the report.
	 */
	void doTraces();

private:
	std::vector<std::pair<std::string,int> > _traceVector;
	void askForTrace(std::string filename, int captured);
};

#endif /* STATISTICS_H_ */
