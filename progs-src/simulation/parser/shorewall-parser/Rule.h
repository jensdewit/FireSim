/**
 * @file Rule.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef RULE_H_
#define RULE_H_

//Standard
#include <vector>
#include <iostream>
#include <string>
//Poco
//FireSim
#include "conditions/Condition.h"

class Chain;

class Rule {
public:

	/**
	 * Constructor
	 * @param Rule in iptables syntax
	 * @param conditions This is a list of conditions corresponding to this rule.
	 * @param target This is the chain jumped to when the condition is satisfied.
	 */
	Rule(std::string iptablesFormat, std::vector<Condition*> conditions, Chain* target);

	/**
	 * Constructor for nat rules.
	 * @param Rule in iptables syntax
	 * @param conditions This is a list of conditions corresponding to this rule.
	 * @param target This is the chain jumped to when the condition is satisfied.
	 * @param natIP The translated IP address.
	 * @param natPort The translated port.
	 */
	Rule(std::string iptablesFormat, std::vector<Condition*> conditions, Chain* target, std::string natIP, std::string natPort);

	/**
	 * Destructor
	 */
	~Rule();

	/**
	 * Returns the next chain if condition of the rule would be satisfied.
	 * @return the next chain.
	 */
	Chain* getJumpChain();

	/**
	 * Verify whether this rule has one or more conditions.
	 * @return The corresponding indication.
	 */
	bool hasCondition();

	/**
	 * Verify whether the rule is assumed to be ignored.
	 */
	bool ignore();

	/**
	 * Checks whether the rule to be scripted needs an IPClassifier,
	 * @return True if a IPClassifier is needed.
	 */
	bool needsIPClassifier();

	/**
	 * Checks whether the rule to be scripted needs a Classifier,
	 * @return True if a Classifier is needed.
	 */
	bool needsClassifier();

	/**
	 * Print a click IPClassifier
	 * @param ostream This is the output stream. The classifier will be printed to this stream.
	 */
	void printClickIPClassifier(std::ostream& ostream);

	/**
	 * Print a click Classifier
	 * @param ostream This is the output stream. The classifier will be printed to this stream.
	 */
	void printClickClassifier(std::ostream& ostream);

	/**
	 * Print a click IPRewriter
	 * @param ostream This is the output stream. The iprewriter will be printed to this stream.
	 *
	 */
	void printIPRewriter(std::ostream& ostream);

	/**
	 * Get the rule in iptable format.
	 * @return the iptable rule
	 */
	std::string getIpTablesText();

private:
	std::string _iptablesFormat;
	std::vector<Condition*> _conditions;
	Chain* _target;
	std::string _natIP;
	std::string _natPort;
};

#endif /* RULE_H_ */
