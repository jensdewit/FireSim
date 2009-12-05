###################################################################

include $(PHOME)/unix/config.mk

###################################################################
# MACROS
###################################################################

DIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d -regex '\.\/[^\.].*')

###################################################################
# Targets
###################################################################

.PHONY: default local.default \
	recurse.tidy local.tidy recurse.clean local.clean

#-------
default: local.default

#-------
recurse.tidy:
	@ $(foreach dir, $(DIRS), $(MAKE) -C $(dir) tidy;)

local.tidy:
	@ $(TIDYDIR)

#-------
recurse.clean:
	@ $(foreach dir, $(DIRS), $(MAKE) -C $(dir) clean;)

local.clean:
	@ $(CLEANDIR)

###################################################################
