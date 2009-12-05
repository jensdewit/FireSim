/**
 * @file Condition.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef CONDITION_H_
#define CONDITION_H_

//Standard
#include <iostream>
//Poco
//FireSim

class Condition {
public:
	/**
	 * Prints the condition in the right form to the stream.
	 */
	virtual void print(std::ostream&) = 0;

};

#endif /* CONDITION_H_ */
