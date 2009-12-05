/**
 * @file ConfigContent.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef CONFIGCONTENT_H_
#define CONFIGCONTENT_H_

//Standard
#include <string>
#include <vector>

//Poco
#include "Poco/Net/IPAddress.h"

using Poco::Net::IPAddress;

enum Protocol {
ICMP = 1,
//IGMP = 2,
//GGP = 3,
//IPIP = 4,
//ST = 5,
TCP = 6,
//UCL = 7,
//EGP = 8,
//IGP = 9,
//BBN = 10,
//NVPII = 11,
//PUP = 12,
//ARGUS = 13,
//EMCON = 14,
//XNET = 15,
//CHAOS = 16,
UDP = 17,
//MUX = 18,
//DCN = 19,
//HMP = 20,
//PRM = 21,
//XNS = 22,
//TRUNK1 = 23,
//TRUNK2 = 24,
//LEAF1 = 25,
//LEAF2 = 26,
//RDP = 27,
//IRTP = 28,
//ISOTP4 = 29,
//NETBLT = 30,
//MFENSP = 31,
//MERIT = 32,
//DCCP = 33,
//ICMP6 = 58,
//CFTP = 62,
//SATNET = 64,
//MITSUBNET = 65,
//RVD = 66,
//IPPC = 67,
//SATMON = 69,
//IPCV = 71,
//BRSATMON = 76,
//WBMON = 78,
//WBEXPAK = 79,
//SCTP = 132,
//UDPLITE = 136,
};

enum Flags{
	URG = 32,
	ACK = 16,
	PSH = 8,
	RST = 4,
	SYN = 2,
	FIN = 1
};

enum Policy{ ACCEPT, REJECT, DROP };

/**
 * ConfigContent, containing fileId,transferPort,...
 */
struct ConfigContent {
	IPAddress sourceIP;
	unsigned short sourcePort;
	IPAddress destIP;
	unsigned short destPort;
	Protocol protocol;
	std::vector<Flags> tcp_flags;
	short icmp_type;
	short icmp_code;
	Policy policy;
	std::string inInterface;
	std::string outInterface;
	std::string dumpPath;
};

#endif /* CONFIGCONTENT_H_ */
