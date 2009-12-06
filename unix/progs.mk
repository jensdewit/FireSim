include $(PHOME)/unix/config.mk

###################################################################
#
# DIRS
#
###################################################################

DIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d -regex '\.\/[^\.].*')

###################################################################
#
# PROGNAMES
#
###################################################################

PROGNAMES =\
	$(PROGNAME1)

###################################################################
#
# Default target, comes first
#
###################################################################

.PHONY: default

default:
	@ $(ECHO) "\ntargets:\n   all\n   progs\n   tidy\n   clean"
	@ $(ECHO) "\nindividual program targets:"
	@ $(ECHO) $(PROGNAMES)| tr ' ' '\n' |sed -s 's/^/   /'
	@ $(ECHO)

###################################################################
#
# Macros & individual program targets
#
###################################################################

ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAMES)
endif

#--------------------

ifneq ($(PROGNAME1), )
ifeq ($(SOURCES1), )
SOURCES1 = $(addsuffix .cpp, $(PROGNAME1))
endif
DEPFILES1 = $(addprefix $(OBJDIR)/,$(SOURCES1:.cpp=.d))
OBJFILES1 = $(addprefix $(OBJDIR)/,$(SOURCES1:.cpp=.o))
EXEFILE1  = $(EXEDIR)/$(PROGNAME1)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME1)
$(PROGNAME1): $(EXEFILE1)
endif
$(EXEFILE1): $(LIB) $(OBJFILES1)
	$(MYLDRULE)
endif

#--------- using sort to remove duplicates

DEPFILES  = $(DEPFILES1)

OBJFILES  = $(OBJFILES1)

EXEFILES  =	$(EXEFILE1)

###################################################################
#
# Global targets for building progs, cleaning etc.
#
###################################################################

.PHONY: recurse.tidy local.tidy recurse.clean local.clean \
	recurse.progs local.progs exedir objdir $(LIBCHECK)

#-------
recurse.tidy:
	@ $(foreach dir, $(DIRS), $(MAKE) -C $(dir) tidy;)

local.tidy:
	@ $(TIDYDIR)
	@ $(RM) $(OBJFILES)

#-------
recurse.clean:
	@ $(foreach dir, $(DIRS), $(MAKE) -C $(dir) clean;)

local.clean:
	@ $(CLEANDIR)
	@ $(RM) $(OBJFILES) $(EXEFILES)

#-------
recurse.progs:
	@ $(foreach dir, $(DIRS), $(MAKE) -C $(dir) progs;)

local.progs: objdir exedir $(EXEFILES)

exedir: 
	@ if [ ! -d $(EXEDIR) ] ; then mkdir -p $(EXEDIR); fi

objdir: 
	@ if [ ! -d $(OBJDIR) ] ; then mkdir -p $(OBJDIR); fi

#-------- See Readme.txt concerning FORCE in this rule
ifneq ($(LIB), )
$(LIB): $(LIBCHECK)
	@ $(MAKE) -C$(PHOME) lib
endif


###################################################################
#
# Rules
#
###################################################################

#---------------------------------------------------------------
#  Rule for dependency files for progs vs headers
#---------------------------------------------------------------

$(DEPFILES):%.d: %.cpp
	@ $(SHELL) -ec '$(MAKEDEPEND) $(CPPFLAGS) $< | sed '\''s@\($*\)\.o[ :]*@$(OBJDIR)/\1.o $@ : @g'\'' > $@'

#---------------------------------------------------------------
#  Pattern rule for building objectfiles in appropriate directory
#---------------------------------------------------------------

$(OBJFILES):$(OBJDIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

#---------------------------------------------------------------
#  MACRO for loading executable in appropriate directory
#---------------------------------------------------------------

MYLDRULE= $(CXX) $(filter %.o, $^) $(LDFLAGS) -o $@


###################################################################
#
# Dependency files
#
###################################################################

ifneq ($(strip $(DEPFILES)),)
-include $(DEPFILES)
endif

###################################################################

