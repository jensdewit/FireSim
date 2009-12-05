####################################################################

PHOME = .
include $(PHOME)/unix/top.mk

###################################################################
# required by the above included section

DIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d -regex '\.\/[^\.].*')

####################################################################

.PHONY: local.default all tidy clean

local.default:
	@ $(ECHO) "targets:"
	@ $(ECHO) "   all\n   tidy\n   clean"

all:
	@ $(MAKE) -C progs-src progs

tidy: recurse.tidy local.tidy

clean: recurse.clean local.clean

####################################################################
