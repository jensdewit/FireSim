###################################################################

include $(PHOME)/unix/config.mk

###################################################################
#
# Targets
#
###################################################################

.PHONY: default local.default \
	recurse.tidy local.tidy recurse.clean local.clean \
	dos2ux ux2dos

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
	$(CLEANDIR)

#-------
dos2ux:
	@ $(ECHO) "setting permissions"
	@ (cd $(PHOME); \
		find . -type d -exec chmod 750 {} \; ; \
		find . -type f -exec chmod 640 {} \; ; )
	@ $(ECHO) "checking newlines"
	@ (cd $(PHOME); \
		find . -type f -name *.cpp -exec $(DOS2UNIX) {} {} \; ; \
		find . -type f -name *.h   -exec $(DOS2UNIX) {} {} \; ; \
		find . -type f -name *.cpp -exec $(DOS2UNIX) {} {} \; ; \
		find . -type f -name *.txt -exec $(DOS2UNIX) {} {} \; ; \
		find . -type f -name Make* -exec $(DOS2UNIX) {} {} \; ; \
		find . -type f -name *.cfg -exec $(DOS2UNIX) {} {} \; ; )

ux2dos:
	@ $(ECHO) "checking newlines"
	@ (cd $(PHOME); \
		find . -type f -name *.cpp -exec $(UNIX2DOS) {} {} \; ; \
		find . -type f -name *.h   -exec $(UNIX2DOS) {} {} \; ; )

###################################################################
