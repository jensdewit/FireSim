/**
 * @file CommandHandler.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

//Standard
#include <string>

//Network
#include "Poco/Net/StreamSocket.h"

class CommandHandler {
public:
	/**
	 * Constructor
	 * @param socket where the click firewall simulation is listening for click commands.
	 */
	CommandHandler(std::string host, int port);

	/**
	 * Destructor
	 */
	virtual ~CommandHandler();

	/**
	 * Send click command to click simulation and return the click reply
	 * @param clickCmd is the click command that must be sent to click.
	 * @return the click reply.
	 */
	std::string execute(std::string clickCmd);
private:
	Poco::Net::StreamSocket _socket;
};
#endif /* COMMANDHANDLER_H_ */
