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
	$(PROGNAME1) $(PROGNAME2) $(PROGNAME3) $(PROGNAME4) $(PROGNAME5)	\
	$(PROGNAME6) $(PROGNAME7) $(PROGNAME8) $(PROGNAME9) $(PROGNAME10)	\
	$(PROGNAME11) $(PROGNAME12) $(PROGNAME13) $(PROGNAME14) $(PROGNAME15)	\
	$(PROGNAME16) $(PROGNAME17) $(PROGNAME18) $(PROGNAME19) $(PROGNAME20)

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
DEPFILES1 = $(SOURCES1:.cpp=.d)
OBJFILES1 = $(addprefix $(OBJDIR)/,$(SOURCES1:.cpp=.o))
EXEFILE1  = $(EXEDIR)/$(PROGNAME1)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME1)
$(PROGNAME1): $(EXEFILE1)
endif
$(EXEFILE1): $(LIB) $(OBJFILES1)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME2), )
ifeq ($(SOURCES2), )
SOURCES2 = $(addsuffix .cpp, $(PROGNAME2))
endif
DEPFILES2 = $(addprefix .,$(SOURCES2:.cpp=.d))
OBJFILES2 = $(addprefix $(OBJDIR)/,$(SOURCES2:.cpp=.o))
EXEFILE2  = $(EXEDIR)/$(PROGNAME2)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME2)
$(PROGNAME2): $(EXEFILE2)
endif
$(EXEFILE2): $(LIB) $(OBJFILES2)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME3), )
ifeq ($(SOURCES3), )
SOURCES3 = $(addsuffix .cpp, $(PROGNAME3))
endif
DEPFILES3 = $(addprefix .,$(SOURCES3:.cpp=.d))
OBJFILES3 = $(addprefix $(OBJDIR)/,$(SOURCES3:.cpp=.o))
EXEFILE3  = $(EXEDIR)/$(PROGNAME3)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME3)
$(PROGNAME3): $(EXEFILE3)
endif
$(EXEFILE3): $(LIB) $(OBJFILES3)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME4), )
ifeq ($(SOURCES4), )
SOURCES4 = $(addsuffix .cpp, $(PROGNAME4))
endif
DEPFILES4 = $(addprefix .,$(SOURCES4:.cpp=.d))
OBJFILES4 = $(addprefix $(OBJDIR)/,$(SOURCES4:.cpp=.o))
EXEFILE4  = $(EXEDIR)/$(PROGNAME4)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME4)
$(PROGNAME4): $(EXEFILE4)
endif
$(EXEFILE4): $(LIB) $(OBJFILES4)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME5), )
ifeq ($(SOURCES5), )
SOURCES5 = $(addsuffix .cpp, $(PROGNAME5))
endif
DEPFILES5 = $(addprefix .,$(SOURCES5:.cpp=.d))
OBJFILES5 = $(addprefix $(OBJDIR)/,$(SOURCES5:.cpp=.o))
EXEFILE5  = $(EXEDIR)/$(PROGNAME5)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME5)
$(PROGNAME5): $(EXEFILE5)
endif
$(EXEFILE5): $(LIB) $(OBJFILES5)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME6), )
ifeq ($(SOURCES6), )
SOURCES6 = $(addsuffix .cpp, $(PROGNAME6))
endif
DEPFILES6 = $(addprefix .,$(SOURCES6:.cpp=.d))
OBJFILES6 = $(addprefix $(OBJDIR)/,$(SOURCES6:.cpp=.o))
EXEFILE6  = $(EXEDIR)/$(PROGNAME6)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME6)
$(PROGNAME6): $(EXEFILE6)
endif
$(EXEFILE6): $(LIB) $(OBJFILES6)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME7), )
ifeq ($(SOURCES7), )
SOURCES7 = $(addsuffix .cpp, $(PROGNAME7))
endif
DEPFILES7 = $(addprefix .,$(SOURCES7:.cpp=.d))
OBJFILES7 = $(addprefix $(OBJDIR)/,$(SOURCES7:.cpp=.o))
EXEFILE7  = $(EXEDIR)/$(PROGNAME7)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME7)
$(PROGNAME7): $(EXEFILE7)
endif
$(EXEFILE7): $(LIB) $(OBJFILES7)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME8), )
ifeq ($(SOURCES8), )
SOURCES8 = $(addsuffix .cpp, $(PROGNAME8))
endif
DEPFILES8 = $(addprefix .,$(SOURCES8:.cpp=.d))
OBJFILES8 = $(addprefix $(OBJDIR)/,$(SOURCES8:.cpp=.o))
EXEFILE8  = $(EXEDIR)/$(PROGNAME8)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME8)
$(PROGNAME8): $(EXEFILE8)
endif
$(EXEFILE8): $(LIB) $(OBJFILES8)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME9), )
ifeq ($(SOURCES9), )
SOURCES9 = $(addsuffix .cpp, $(PROGNAME9))
endif
DEPFILES9 = $(addprefix .,$(SOURCES9:.cpp=.d))
OBJFILES9 = $(addprefix $(OBJDIR)/,$(SOURCES9:.cpp=.o))
EXEFILE9  = $(EXEDIR)/$(PROGNAME9)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME9)
$(PROGNAME9): $(EXEFILE9)
endif
$(EXEFILE9): $(LIB) $(OBJFILES9)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME10), )
ifeq ($(SOURCES10), )
SOURCES10 = $(addsuffix .cpp, $(PROGNAME10))
endif
DEPFILES10 = $(addprefix .,$(SOURCES10:.cpp=.d))
OBJFILES10 = $(addprefix $(OBJDIR)/,$(SOURCES10:.cpp=.o))
EXEFILE10  = $(EXEDIR)/$(PROGNAME10)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME10)
$(PROGNAME10): $(EXEFILE10)
endif
$(EXEFILE10): $(LIB) $(OBJFILES10)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME11), )
ifeq ($(SOURCES11), )
SOURCES11 = $(addsuffix .cpp, $(PROGNAME11))
endif
DEPFILES11 = $(addprefix .,$(SOURCES11:.cpp=.d))
OBJFILES11 = $(addprefix $(OBJDIR)/,$(SOURCES11:.cpp=.o))
EXEFILE11  = $(EXEDIR)/$(PROGNAME11)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME11)
$(PROGNAME11): $(EXEFILE11)
endif
$(EXEFILE11): $(LIB) $(OBJFILES11)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME12), )
ifeq ($(SOURCES12), )
SOURCES12 = $(addsuffix .cpp, $(PROGNAME12))
endif
DEPFILES12 = $(addprefix .,$(SOURCES12:.cpp=.d))
OBJFILES12 = $(addprefix $(OBJDIR)/,$(SOURCES12:.cpp=.o))
EXEFILE12  = $(EXEDIR)/$(PROGNAME12)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME12)
$(PROGNAME12): $(EXEFILE12)
endif
$(EXEFILE12): $(LIB) $(OBJFILES12)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME13), )
ifeq ($(SOURCES13), )
SOURCES13 = $(addsuffix .cpp, $(PROGNAME13))
endif
DEPFILES13 = $(addprefix .,$(SOURCES13:.cpp=.d))
OBJFILES13 = $(addprefix $(OBJDIR)/,$(SOURCES13:.cpp=.o))
EXEFILE13  = $(EXEDIR)/$(PROGNAME13)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME13)
$(PROGNAME13): $(EXEFILE13)
endif
$(EXEFILE13): $(LIB) $(OBJFILES13)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME14), )
ifeq ($(SOURCES14), )
SOURCES14 = $(addsuffix .cpp, $(PROGNAME14))
endif
DEPFILES14 = $(addprefix .,$(SOURCES14:.cpp=.d))
OBJFILES14 = $(addprefix $(OBJDIR)/,$(SOURCES14:.cpp=.o))
EXEFILE14  = $(EXEDIR)/$(PROGNAME14)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME14)
$(PROGNAME14): $(EXEFILE14)
endif
$(EXEFILE14): $(LIB) $(OBJFILES14)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME15), )
ifeq ($(SOURCES15), )
SOURCES15 = $(addsuffix .cpp, $(PROGNAME15))
endif
DEPFILES15 = $(addprefix .,$(SOURCES15:.cpp=.d))
OBJFILES15 = $(addprefix $(OBJDIR)/,$(SOURCES15:.cpp=.o))
EXEFILE15  = $(EXEDIR)/$(PROGNAME15)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME15)
$(PROGNAME15): $(EXEFILE15)
endif
$(EXEFILE15): $(LIB) $(OBJFILES15)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME16), )
ifeq ($(SOURCES16), )
SOURCES16 = $(addsuffix .cpp, $(PROGNAME16))
endif
DEPFILES16 = $(addprefix .,$(SOURCES16:.cpp=.d))
OBJFILES16 = $(addprefix $(OBJDIR)/,$(SOURCES16:.cpp=.o))
EXEFILE16  = $(EXEDIR)/$(PROGNAME16)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME16)
$(PROGNAME16): $(EXEFILE16)
endif
$(EXEFILE16): $(LIB) $(OBJFILES16)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME17), )
ifeq ($(SOURCES17), )
SOURCES17 = $(addsuffix .cpp, $(PROGNAME17))
endif
DEPFILES17 = $(addprefix .,$(SOURCES17:.cpp=.d))
OBJFILES17 = $(addprefix $(OBJDIR)/,$(SOURCES17:.cpp=.o))
EXEFILE17  = $(EXEDIR)/$(PROGNAME17)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME17)
$(PROGNAME17): $(EXEFILE17)
endif
$(EXEFILE17): $(LIB) $(OBJFILES17)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME18), )
ifeq ($(SOURCES18), )
SOURCES18 = $(addsuffix .cpp, $(PROGNAME18))
endif
DEPFILES18 = $(addprefix .,$(SOURCES18:.cpp=.d))
OBJFILES18 = $(addprefix $(OBJDIR)/,$(SOURCES18:.cpp=.o))
EXEFILE18  = $(EXEDIR)/$(PROGNAME18)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME18)
$(PROGNAME18): $(EXEFILE18)
endif
$(EXEFILE18): $(LIB) $(OBJFILES18)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME19), )
ifeq ($(SOURCES19), )
SOURCES19 = $(addsuffix .cpp, $(PROGNAME19))
endif
DEPFILES19 = $(addprefix .,$(SOURCES19:.cpp=.d))
OBJFILES19 = $(addprefix $(OBJDIR)/,$(SOURCES19:.cpp=.o))
EXEFILE19  = $(EXEDIR)/$(PROGNAME19)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME19)
$(PROGNAME19): $(EXEFILE19)
endif
$(EXEFILE19): $(LIB) $(OBJFILES19)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME20), )
ifeq ($(SOURCES20), )
SOURCES20 = $(addsuffix .cpp, $(PROGNAME20))
endif
DEPFILES20 = $(addprefix .,$(SOURCES20:.cpp=.d))
OBJFILES20 = $(addprefix $(OBJDIR)/,$(SOURCES20:.cpp=.o))
EXEFILE20  = $(EXEDIR)/$(PROGNAME20)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME20)
$(PROGNAME20): $(EXEFILE20)
endif
$(EXEFILE20): $(LIB) $(OBJFILES20)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME21), )
ifeq ($(SOURCES21), )
SOURCES21 = $(addsuffix .cpp, $(PROGNAME21))
endif
DEPFILES21 = $(addprefix .,$(SOURCES21:.cpp=.d))
OBJFILES21 = $(addprefix $(OBJDIR)/,$(SOURCES21:.cpp=.o))
EXEFILE21  = $(EXEDIR)/$(PROGNAME21)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME21)
$(PROGNAME21): $(EXEFILE21)
endif
$(EXEFILE21): $(LIB) $(OBJFILES21)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME22), )
ifeq ($(SOURCES22), )
SOURCES22 = $(addsuffix .cpp, $(PROGNAME22))
endif
DEPFILES22 = $(addprefix .,$(SOURCES22:.cpp=.d))
OBJFILES22 = $(addprefix $(OBJDIR)/,$(SOURCES22:.cpp=.o))
EXEFILE22  = $(EXEDIR)/$(PROGNAME22)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME22)
$(PROGNAME22): $(EXEFILE22)
endif
$(EXEFILE22): $(LIB) $(OBJFILES22)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME23), )
ifeq ($(SOURCES23), )
SOURCES23 = $(addsuffix .cpp, $(PROGNAME23))
endif
DEPFILES23 = $(addprefix .,$(SOURCES23:.cpp=.d))
OBJFILES23 = $(addprefix $(OBJDIR)/,$(SOURCES23:.cpp=.o))
EXEFILE23  = $(EXEDIR)/$(PROGNAME23)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME23)
$(PROGNAME23): $(EXEFILE23)
endif
$(EXEFILE23): $(LIB) $(OBJFILES23)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME24), )
ifeq ($(SOURCES24), )
SOURCES24 = $(addsuffix .cpp, $(PROGNAME24))
endif
DEPFILES24 = $(addprefix .,$(SOURCES24:.cpp=.d))
OBJFILES24 = $(addprefix $(OBJDIR)/,$(SOURCES24:.cpp=.o))
EXEFILE24  = $(EXEDIR)/$(PROGNAME24)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME24)
$(PROGNAME24): $(EXEFILE24)
endif
$(EXEFILE24): $(LIB) $(OBJFILES24)
	$(MYLDRULE)
endif

ifneq ($(PROGNAME25), )
ifeq ($(SOURCES25), )
SOURCES25 = $(addsuffix .cpp, $(PROGNAME25))
endif
DEPFILES25 = $(addprefix .,$(SOURCES25:.cpp=.d))
OBJFILES25 = $(addprefix $(OBJDIR)/,$(SOURCES25:.cpp=.o))
EXEFILE25  = $(EXEDIR)/$(PROGNAME25)
ifneq ($(EXEDIR), .)
.PHONY: $(PROGNAME25)
$(PROGNAME25): $(EXEFILE25)
endif
$(EXEFILE25): $(LIB) $(OBJFILES25)
	$(MYLDRULE)
endif

#--------- using sort to remove duplicates

DEPFILES  = $(sort \
	$(DEPFILES1) $(DEPFILES2) $(DEPFILE3) $(DEPFILES4) $(DEPFILES5)		\
	$(DEPFILES6) $(DEPFILES7) $(DEPFILE8) $(DEPFILES9) $(DEPFILES10)	\
	$(DEPFILES11) $(DEPFILES12) $(DEPFILE13) $(DEPFILES14) $(DEPFILES15)	\
	$(DEPFILES16) $(DEPFILES17) $(DEPFILE18) $(DEPFILES19) $(DEPFILES20)	\
	$(DEPFILES21) $(DEPFILES22) $(DEPFILES23) $(DEPFILES24) $(DEPFILES25)	\
	)

OBJFILES  = $(sort \
	$(OBJFILES1) $(OBJFILES2) $(OBJFILES3) $(OBJFILES4) $(OBJFILES5)	\
	$(OBJFILES6) $(OBJFILES7) $(OBJFILES8) $(OBJFILES9) $(OBJFILES10)	\
	$(OBJFILES11) $(OBJFILES12) $(OBJFILES13) $(OBJFILES14) $(OBJFILES15)	\
	$(OBJFILES16) $(OBJFILES17) $(OBJFILES18) $(OBJFILES19) $(OBJFILES20)	\
	$(OBJFILES21) $(OBJFILES22) $(OBJFILES23) $(OBJFILES24) $(OBJFILES25)	\
	)

EXEFILES  =\
	$(EXEFILE1) $(EXEFILE2) $(EXEFILE3) $(EXEFILE4) $(EXEFILE5)		\
	$(EXEFILE6) $(EXEFILE7) $(EXEFILE8) $(EXEFILE9) $(EXEFILE10)		\
	$(EXEFILE11) $(EXEFILE12) $(EXEFILE13) $(EXEFILE14) $(EXEFILE15)	\
	$(EXEFILE16) $(EXEFILE17) $(EXEFILE18) $(EXEFILE19) $(EXEFILE20)	\
	$(EXEFILE21) $(EXEFILE22) $(EXEFILE23) $(EXEFILE24) $(EXEFILE25)

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

