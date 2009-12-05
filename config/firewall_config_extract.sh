#!/bin/bash

#######################################
#authors: Nico Van Looy & Jens De Wit #
#FireSim - University of Antwerp 2009 #
#######################################

##############################
#Generate network_layout.xml #
##############################

#
#settings
#
outputXMLFile="network_layout.xml"

#
# Issue a message and exit
#
fatal_error()
{
    echo "   ERROR: $@" >&2
    exit 1
}

#include some helper functions
get_interface_bcasts() # $1 = interface
{
    ip -f inet addr show dev $1 2> /dev/null | grep 'inet.*brd' | sed 's/inet.*brd //; s/scope.*//;' | sort -u 
}

find_first_interface_address_if_any() # $1 = interface
{
    #
    # get the line of output containing the first IP address
    #
    addr=$(ip -f inet addr show $1 2> /dev/null | grep 'inet .* global' | head -n1)
    #
    # Strip off the trailing VLSM mask (or the peer IP in case of a P-t-P link)
    # along with everything else on the line
    #
    [ -n "$addr" ] && echo $addr | sed 's/\s*inet //;s/\/.*//;s/ peer.*//' || echo 0.0.0.0
}

#
# Process each interface and generate corresponding xml
#
processInterfaceXML(){
	line="$@" # get all args
	interface=$(echo $line | awk -F: '{ print $2 }' | awk '{ print $1 }' | sed 's/@.*$//')

	if [ -n "$(ip link list dev $interface 2> /dev/null | grep -e '[<,]UP[,>]')" ];
	then
		status='"up"'
	else
		status='"down"'
	fi
	
	echo "	<INTERFACE status=$status>" >> $outputXMLFile
	echo "		<NAME>$interface</NAME>" >> $outputXMLFile
	
	mac=`ifconfig $interface | grep HWaddr | sed 's/.*HWaddr //;s/[ ]*$//'`
	if [ -n "$mac" ];
	then
		echo "		<MAC_ADDRESS>$mac</MAC_ADDRESS>" >> $outputXMLFile
	fi
	
	echo "		<IP_ADDRESS>`find_first_interface_address_if_any $interface`</IP_ADDRESS>" >> $outputXMLFile
	
	mask=`ifconfig $interface | grep Mask: | sed 's/.*Mask://'`
	if [ -n "$mask" ];
	then
	  	echo "		<MASK>$mask</MASK>" >> $outputXMLFile
	fi
	
	bcast=`get_interface_bcasts $interface`
	if [ -n "$bcast" ];
	then
		echo "		<BROADCAST>`echo $bcast | sed 's/^[ ]*//'`</BROADCAST>" >> $outputXMLFile
  	fi
  

	
  echo "	</INTERFACE>" >> $outputXMLFile
}

##############################
#Generate script_vars.sh     #
##############################

#
#settings
#
outputVarsFile="script_vars.sh"

#
#  echo the list of networks routed out of a given interface
#
get_routed_networks() # $1 = interface name, $2-n = Fatal error message
{
    local address
    local rest

    ip route show dev $1 2> /dev/null |
	while read address rest; do
	    case "$address" in
		default)
		    if [ $# -gt 1 ]; then
			shift
			fatal_error "$@"
		    fi
		    ;;
		multicast|broadcast|prohibit|nat|throw|nexthop)
		    ;;
		*)
		    echo $address
		    ;;
	    esac
        done
}

#
# Convert argument to uppercase
#
toUpper() {
  echo $1 | tr "[:lower:]" "[:upper:]" 
}

#
# Process each interface and generate corresponding variables
#
processInterfaceVars(){
	line="$@" # get all args
	interface=$(echo $line | awk -F: '{ print $2 }' | awk '{ print $1 }')
	networks=$(get_routed_networks $interface)
	if [ -n "$networks" ]
	then
		echo `toUpper $interface`"_NETWORKS="$networks >> $outputVarsFile
	fi
}


# 
#main procedure
#

#networklayout.xml
echo "" > $outputXMLFile #clears file
echo "<NETWORK_LAYOUT>" >> $outputXMLFile

#process each interface
ip -o link |
while read line
do
	# use $line variable to process line in processLine() function
	processInterfaceXML $line
done

echo "</NETWORK_LAYOUT>" >> $outputXMLFile

#script_vars.sh
echo "" > $outputVarsFile
#process each interface
ip -o link |
while read line
do
	# use $line variable to process line in processLine() function
	processInterfaceVars $line
done

echo "Files $outputXMLFile en $outputVarsFile generated in present working directory."
exit 0
