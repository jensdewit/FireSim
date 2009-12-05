###################################################################

#------------------------------------------------------
# Project name and version.
#------------------------------------------------------
PNAME    = firewallsimulation
PVERSION =

#------------------------------------------------------
# Where to find the Poco libraries?
#------------------------------------------------------
POCO = /usr/local/lib

#------------------------------------------------------
# Platform name (PFN) & development environment (DPFN)
# COPT can be GNU or NATIVE
#------------------------------------------------------
COPT = GNU

# Vanilla Linux
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	PFN = linux
endif
#Contributed by K. Overdulve for MacOS X
ifeq ($(strip $(UNAME)),Darwin)
 PFN := darwin
endif

DPFN = $(PFN)_$(COPT)

#------------------------------------------------------
# Location for binary files
#------------------------------------------------------
EXEDIR   = $(PHOME)/bin/$(PFN)
#EXEDIR   = $(HOME)/bin/$(PFN)/$(PNAME)
#EXEDIR   = .

OBJDIR   = $(PHOME)/obj/$(PFN)
#OBJDIR   = $(HOME)/obj/$(PFN)/$(PNAME)
#OBJDIR   = .

#------------------------------------------------------
# Location for project static library file
#------------------------------------------------------
#LIBNAME  = $(PNAME)$(PVERSION)
#LIBDIR	 = $(PHOME)/lib/$(PFN)
#LIBDIR	 = $(HOME)/lib/$(PFN)

ifneq ($(LIBNAME), )
LIB	 = $(LIBDIR)/lib$(LIBNAME).a
endif

#------------------------------------------------------
# Project include files
#------------------------------------------------------
PROJINCLUDES=\
	-I$(PHOME)/progs-src/simulation/includes 

#------------------------------------------------------
# External include and library dirs
#------------------------------------------------------
EXTINCLUDEDIRS    = -I/usr/include
EXTARCHIVELIBS    = -lcppunit
EXTARCHIVELIBDIRS = -L/lib -L/lib64 -L/usr/local/lib

#------------------------------------------------------
# Pre-processing options
#------------------------------------------------------
INCLUDES = $(PROJINCLUDES) $(EXTINCLUDEDIRS)
DEFINES  = -D$(PFN) -D$(DPFN)
CPPFLAGS = $(INCLUDES) $(DEFINES)

#------------------------------------------------------
# Options for processing .cpp files
#------------------------------------------------------
OPTLEV = -O
#
CXXFLAGS = $(OPTLEV)

ifeq ($(DPFN), solaris_NATIVE)
    CXX      = CC
    CXXFLAGS += -features=no%anachronisms -w
endif
ifeq ($(COPT), GNU)
	CXX       = g++
	CXXFLAGS += 
	DEFINES  += -DGNU
endif

#------------------------------------------------------
# Options for linking
#------------------------------------------------------
ifeq ($(COPT), GNU)
LDOPT    = $(POCO)/libPocoFoundation.so $(POCO)/libPocoNet.so $(POCO)/libPocoUtil.so -Wl,-R $(POCO) 
endif
	   
ifneq ($(LIBNAME), )
LDLIBS   = -L$(LIBDIR) -l$(LIBNAME)
endif
LDLIBS   += $(EXTARCHIVELIBDIRS) $(EXTARCHIVELIBS)

LDFLAGS += $(LDLIBS) $(LDOPT)

#------------------------------------------------------
# Options for dependence of progs on lib
#------------------------------------------------------
# When building progs, first do a full check on whether $(LIB)
# is up to date wrt its dependencies --> LIBCHECK = FORCE
# When building progs, just check that $(LIB) exits, and rebuild
# progs if $(LIB) is more recent --> LIBCHECK = 
LIBCHECK = FORCE

###################################################################
#
# GENERAL RULES and COMMAND VARS
#
###################################################################

#-----------------------------------------------------------
# Miscellaneous command vars
#-----------------------------------------------------------

DOS2UNIX   = dos2unix
UNIX2DOS   = unix2dos
RM         = rm -f
ECHO       = echo
MAKEDEPEND = gcc -MM
ifeq ($(PFN), solaris)
ECHO     = echo
endif

#------------------------------------------------------------
# Commands for tidying and cleaning up
#------------------------------------------------------------

TIDYDIR = \
        @ $(ECHO) tyding up `pwd`; \
        $(RM) -f core *.o *~ *.bak *.I .*.d~

CLEANDIR = \
        @ $(ECHO) cleaning `pwd`; \
        $(RM) -f core *.o *~ *.bak *.I *.d .*.d .*.d~;

#------------------------------------------------------------
# Set suffixes we can deal with
#------------------------------------------------------------

.SUFFIXES:
.SUFFIXES: .cpp .c .o .d .h .a

