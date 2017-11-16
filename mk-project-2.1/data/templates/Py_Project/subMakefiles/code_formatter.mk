#################### [START] Code formatters configuration [START] #############

OVERWRITE = F

USE_PINDENT = %s

USE_TABS = %s

INDENTATION = %d

PINDENT = $(call FILE_EXIST, pindent.py)

#################### [END] Code formatters configuration [END] #################

#################### [START] pindent tool variables [START] ####################

ifeq ($(USE_PINDENT),T)

ifeq ($(PINDENT),T)

ifneq ($(FIND), )

.PHONY: pindent

PINDENT_OPTS =

ifeq ($(USE_TABS),T)
PINDENT_OPTS +=
endif

ifeq ($(USE_TABS),F)
PINDENT_OPTS += -e
endif

PINDENT_OPTS += -t $(INDENTATION) -s $(INDENTATION)

pindent:
	$(FIND) $(SRC_DIR) -iregex .*\.py -exec $(INTERPRETER) pindent.py -c $(PINDENT_OPTS) {} \;
	$(FIND) $(SRC_DIR) -iregex .*\.py -exec $(INTERPRETER) pindent.py -r $(PINDENT_OPTS) {} \;
	$(FIND) $(SRC_DIR) -iregex .*\.py -exec $(INTERPRETER) pindent.py -d $(PINDENT_OPTS) {} \;

else

$(warning Install the find-utils package !)

endif  # FIND

else

$(error Cannot find the pindent.py script !)

endif  # PINDENT

endif  # USE_PINDENT