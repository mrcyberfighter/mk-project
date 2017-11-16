# No license prefixing, you are free to use the license you want.

#################### [START] Documentation settings [START] ####################

USE_SPHINX=%s

RST2MAN = $(call BINARY_EXIST,rst2man)

#################### [END] Documentation settings [END] ####################

#################### [START] Displaying documentation targets [START] ##########

ifneq ($(INFO), )
.PHONY: show-info
show-info:
ifeq ($(call FILE_EXIST, $(INFO_FILE)),T)
	$(INFO) -f $(INFO_FILE)
else
ifeq ($(MAKECMDGOALS),show-info)
$(warning info file not yet builded)
endif
endif
endif

ifneq ($(MAN), )
.PHONY: show-man
show-man:
ifeq ($(call FILE_EXIST, $(MAN_FILE)),T)
	$(MAN) -l $(MAN_FILE)
else
ifeq ($(MAKECMDGOALS),show-man)
$(warning man file not yet builded)
endif
endif
endif

ifneq ($(BROWSER), )
.PHONY: show-html
show-html:
ifeq ($(call FILE_EXIST, $(HTML_FILE)),T)
	$(BROWSER) $(HTML_FILE)
else
ifeq ($(MAKECMDGOALS),show-html)
$(warning html file not yet builded)
endif
endif
endif

ifneq ($(BROWSER), )
.PHONY: show-html5
show-html5:
ifeq ($(call FILE_EXIST, $(HTML5_FILE)),T)
	$(BROWSER) $(HTML5_FILE)
else
ifeq ($(MAKECMDGOALS),show-html5)
$(warning html5 file not yet builded)
endif
endif
endif

ifneq ($(BROWSER), )
.PHONY: show-xml
show-xml:
ifeq ($(call FILE_EXIST, $(XML_FILE)),T)
	$(BROWSER) $(XML_FILE)
else
ifeq ($(MAKECMDGOALS),show-xml)
$(warning xml file not yet builded)
endif
endif
endif

ifneq ($(ODT), )
.PHONY: show-odt
show-odt:
ifeq ($(call FILE_EXIST, $(ODT_FILE)),T)
	$(ODT) $(ODT_FILE)
else
ifeq ($(MAKECMDGOALS),show-odt)
$(warning odt file not yet builded)
endif
endif
endif


ifneq ($(PDF), )
.PHONY: show-pdf
show-pdf:
ifeq ($(call FILE_EXIST, $(PDF_FILE)),T)
	$(PDF) $(PDF_FILE)
else
ifeq ($(MAKECMDGOALS),show-pdf)
$(warning pdf file not yet builded)
endif
endif
endif

ifneq ($(EPUB), )
.PHONY: show-epub
show-epub:
ifeq ($(call FILE_EXIST, $(EPUB_FILE)),T)
	$(EPUB) $(EPUB_FILE)
else
ifeq ($(MAKECMDGOALS),show-epub)
$(warning epub file not yet builded)
endif
endif
endif



#################### [END] Displaying documentation targets [END] ##########
