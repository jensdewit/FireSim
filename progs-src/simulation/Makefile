####################################################################

PHOME   = ../..
CFGSDIR = $(PHOME)/unix

####################################################################

PROGNAME1  = firewallsimulation
SOURCES1   = Main.cpp \
clickgenerator/ClickGenerator.cpp \
parser/shorewall-parser/ShorewallParser.cpp parser/shorewall-parser/ChainParser.cpp \
parser/shorewall-parser/RuleParser.cpp parser/shorewall-parser/Table.cpp \
parser/shorewall-parser/Chain.cpp parser/shorewall-parser/Rule.cpp parser/shorewall-parser/ScriptResolver.cpp \
parser/shorewall-parser/conditions/ConditionFactory.cpp \
parser/config-parser/ConfigParser.cpp parser/config-parser/XmlTagConstants.cpp \
parser/config-parser/PolicyFactory.cpp parser/config-parser/ProtocolFactory.cpp \
parser/network-parser/NetworkParser.cpp parser/network-parser/XmlTagConstants.cpp \
parser/network-parser/NetworkLayout.cpp \
statistics/Statistics.cpp statistics/CommandHandler.cpp \
util/Util.cpp \

####################################################################

include $(CFGSDIR)/progs.mk

####################################################################

.PHONY: tidy clean all progs

tidy: recurse.tidy local.tidy

clean: recurse.clean local.clean

all: progs

progs: recurse.progs local.progs

####################################################################

