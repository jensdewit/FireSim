####################################################################

PHOME   = ..
CFGSDIR = $(PHOME)/unix

####################################################################

include $(CFGSDIR)/progs.mk

####################################################################

.PHONY: tidy clean all progs

tidy: recurse.tidy local.tidy

clean: recurse.clean local.clean

all: progs

progs: recurse.progs local.progs

####################################################################
