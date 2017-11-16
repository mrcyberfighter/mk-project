# No license prefixing, you are free to use the license you want.

#################### [START] Code formatters configuration [START] #############

OVERWRITE = F

USE_INDENT = %s

USE_ASTYLE = %s

USE_BCPP = %s

USE_TABS = %s

INDENTATION = %d

# Edit your options like you want for target indent-user.
INDENT_OPTS = %s

# Edit your options like you want for target astyle-user.
ASTYLE_OPTS = %s

#################### [END] Code formatters configuration [END] #############

#################### [START] indent tool variables [START] #####################

ifeq ($(USE_INDENT),T)

INDENT  = $(call BINARY_EXIST, indent)


INDENT_GNU     = --gnu-style

SRC_FILES_SUFFIX_GNU = $(SRC_FILES:$(EXT_SRC)=-gnu$(EXT_SRC))

HDR_FILES_SUFFIX_GNU = $(HDR_FILES:$(EXT_HDR)=-gnu$(EXT_HDR))


INDENT_LINUX   = --linux-style

SRC_FILES_SUFFIX_LINUX     = $(SRC_FILES:$(EXT_SRC)=-linux$(EXT_SRC))

HDR_FILES_SUFFIX_LINUX = $(HDR_FILES:$(EXT_HDR)=-linux$(EXT_HDR))


INDENT_KR      = --k-and-r-style

SRC_FILES_SUFFIX_KR      = $(SRC_FILES:$(EXT_SRC)=-kr$(EXT_SRC))

HDR_FILES_SUFFIX_KR = $(HDR_FILES:$(EXT_HDR)=-kr$(EXT_HDR))


INDENT_ORIG    = --original

SRC_FILES_SUFFIX_ORIG = $(SRC_FILES:$(EXT_SRC)=-orig$(EXT_SRC))

HDR_FILES_SUFFIX_ORIG = $(HDR_FILES:$(EXT_HDR)=-orig$(EXT_HDR))


SRC_FILES_SUFFIX_USER = $(SRC_FILES:$(EXT_SRC)=-user$(EXT_SRC))

HDR_FILES_SUFFIX_USER = $(HDR_FILES:$(EXT_HDR)=-user$(EXT_HDR))


ifneq ($(INDENT), )
  ifeq ($(MAKECMDGOALS),indent-gnu)
    FMT_SUFFIX_SRC=-gnu$(EXT_SRC)
    FMT_SUFFIX_HDR=-gnu$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),indent-linux)
    FMT_SUFFIX_SRC=-linux$(EXT_SRC)
    FMT_SUFFIX_HDR=-linux$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),indent-kr)
    FMT_SUFFIX_SRC=-kr$(EXT_SRC)
    FMT_SUFFIX_HDR=-kr$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),indent-orig)
    FMT_SUFFIX_SRC=-orig$(EXT_SRC)
    FMT_SUFFIX_HDR=-orig$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),indent-user)
    FMT_SUFFIX_SRC=-user$(EXT_SRC)
    FMT_SUFFIX_HDR=-user$(EXT_HDR)
  endif

endif



#################### [END] indent tool variables [END] #########################


#################### [START] indent tool targets [START] #######################

ifneq ($(INDENT), )

OVERWRITE = F

ifeq ($(USE_TABS),F)
INDENT_USE_TABULATIONS = --no-tabs # --use-tabs
endif

ifeq ($(USE_TABS),T)
INDENT_USE_TABULATIONS = --use-tabs
endif

INDENT_PRIVATE_OPTS = --indent-level$(INDENTATION) -lc4096



#FMT_SUFFIX=.c

ifneq ($(OVERWRITE),T)
indent-kr:
	@for v in $(SRC_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC) $(INDENT_KR) $(INDENT_USE_TABULATIONS) $(INDENT_PRIVATE_OPTS) ;  done ;
	@for v in $(HDR_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR) $(INDENT_KR) $(INDENT_USE_TABULATIONS) $(INDENT_PRIVATE_OPTS) ;  done ;
	@echo "Files formatted in kr-style as: $(SRC_FILES_SUFFIX_KR)"
	@echo "Files formatted in kr-style as: $(HDR_FILES_SUFFIX_KR)"
else
indent-kr:
	$(INDENT) $(SRC_FILES) $(INDENT_KR) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	$(INDENT) $(HDR_FILES) $(INDENT_KR) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	@echo 'Code formatting done'
	@echo "Backup files ($(EXT_SRC)~) created from $(INDENT)"
endif

ifneq ($(OVERWRITE),T)
indent-gnu:
	@for v in $(SRC_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC) $(INDENT_GNU) $(INDENT_USE_TABULATIONS) $(INDENT_PRIVATE_OPTS) ; done ;
	@for v in $(HDR_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR) $(INDENT_GNU) $(INDENT_USE_TABULATIONS) $(INDENT_PRIVATE_OPTS) ; done ;
	@echo "Files formatted in gnu-style as: $(SRC_FILES_SUFFIX_GNU)"
	@echo "Files formatted in gnu-style as: $(HDR_FILES_SUFFIX_GNU)"
else
indent-gnu:
	$(INDENT) $(SRC_FILES) $(INDENT_GNU) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	$(INDENT) $(HDR_FILES) $(INDENT_GNU) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	@echo 'Code formatting done'
	@echo "Backup files ($(EXT_SRC)~) created from $(INDENT)"
endif

ifneq ($(OVERWRITE),T)
indent-linux:
	@for v in $(SRC_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC) $(INDENT_USE_TABULATIONS) $(INDENT_LINUX)  ; done ;
	@for v in $(HDR_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR) $(INDENT_USE_TABULATIONS) $(INDENT_LINUX)  ; done ;
	@echo "Files formatted in linux-style as: $(SRC_FILES_SUFFIX_LINUX)"
	@echo "Files formatted in linux-style as: $(HDR_FILES_SUFFIX_LINUX)"
else
indent-linux:
	$(INDENT) $(SRC_FILES) $(INDENT_LINUX) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	$(INDENT) $(HDR_FILES) $(INDENT_LINUX) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	@echo 'Code formatting done'
	@echo "Backup files ($(EXT_SRC)~) created from $(INDENT)"
endif

ifneq ($(OVERWRITE),T)
indent-orig:
	@for v in $(SRC_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC) $(INDENT_ORIG) $(INDENT_USE_TABULATIONS) $(INDENT_PRIVATE_OPTS) ; done ;
	@for v in $(HDR_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR) $(INDENT_ORIG) $(INDENT_USE_TABULATIONS) $(INDENT_PRIVATE_OPTS) ; done ;
	@echo "Files formatted in original-style as: $(SRC_FILES_SUFFIX_ORIG)"
	@echo "Files formatted in original-style as: $(HDR_FILES_SUFFIX_ORIG)"
else
indent-orig:
	$(INDENT) $(SRC_FILES) $(INDENT_ORIG) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	$(INDENT) $(HDR_FILES) $(INDENT_ORIG) $(INDENT_USE_TABULATIONS)  # Will format and overwrite your source files with making a backup file.
	@echo 'Code formatting done'
	@echo "Backup files ($(EXT_SRC)~) created from $(INDENT)"
	@echo "Backup files ($(EXT_HDR)~) created from $(INDENT)"
endif

ifneq ($(OVERWRITE),T)
indent-user:
	@for v in $(SRC_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC) $(INDENT_USE_TABULATIONS) $(INDENT_OPTS) ; done ;
	@for v in $(HDR_FILES) ; do $(INDENT) $$v -o "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR) $(INDENT_USE_TABULATIONS) $(INDENT_OPTS) ; done ;
	@echo "Files formatted in original-style as: $(SRC_FILES_SUFFIX_USER)"
	@echo "Files formatted in original-style as: $(HDR_FILES_SUFFIX_USER)"
else
indent-user:
	$(INDENT) $(SRC_FILES) $(INDENT_USE_TABULATIONS) $(INDENT_OPTS) $(INDENT_PRIVATE_OPTS)
	$(INDENT) $(HDR_FILES) $(INDENT_USE_TABULATIONS) $(INDENT_OPTS) $(INDENT_PRIVATE_OPTS)
# indent will make a backup file.
endif

.PHONY: indent-clean
indent-clean:
	- $(RM) -f $(SRC_FILES_SUFFIX_KR) $(HDR_FILES_SUFFIX_KR) \
	           $(SRC_FILES_SUFFIX_GNU) $(HDR_FILES_SUFFIX_GNU) \
	           $(SRC_FILES_SUFFIX_ORIG) $(HDR_FILES_SUFFIX_ORIG) \
	           $(SRC_FILES_SUFFIX_LINUX) $(HDR_FILES_SUFFIX_LINUX) \
	           $(SRC_FILES_SUFFIX_USER) $(HDR_FILES_SUFFIX_USER)


else

$(warning Install the indent package !!!)

endif

endif # USE_INDENT

#################### [END] indent tool targets [END] ###########################



#################### [START] astyle tool variables [START] #####################

ifeq ($(USE_ASTYLE),T)

ASTYLE  = $(call BINARY_EXIST, astyle)

ifneq ($(ASTYLE), )




ASTYLE_ANSI     = --style=ansi

SRC_FILES_SUFFIX_ANSI = $(SRC_FILES:$(EXT_SRC)=-ansi$(EXT_SRC))

HDR_FILES_SUFFIX_ANSI = $(HDR_FILES:$(EXT_HDR)=-ansi$(EXT_HDR))


ASTYLE_JAVA   = --style=java

SRC_FILES_SUFFIX_JAVA     = $(SRC_FILES:$(EXT_SRC)=-java$(EXT_SRC))

HDR_FILES_SUFFIX_JAVA     = $(HDR_FILES:$(EXT_HDR)=-java$(EXT_HDR))


ASTYLE_KR      = --style=kr

SRC_FILES_SUFFIX_KR      = $(SRC_FILES:$(EXT_SRC)=-kr$(EXT_SRC))

HDR_FILES_SUFFIX_KR = $(HDR_FILES:$(EXT_HDR)=-kr$(EXT_HDR))


ASTYLE_STROUSTRUP    = --style=stroustrup

SRC_FILES_SUFFIX_STROUSTRUP = $(SRC_FILES:$(EXT_SRC)=-stroustrup$(EXT_SRC))

HDR_FILES_SUFFIX_STROUSTRUP = $(HDR_FILES:$(EXT_HDR)=-stroustrup$(EXT_HDR))


ASTYLE_WHITESMITH    = --style=whitesmith

SRC_FILES_SUFFIX_WHITESMITH = $(SRC_FILES:$(EXT_SRC)=-whitesmith$(EXT_SRC))

HDR_FILES_SUFFIX_WHITESMITH = $(HDR_FILES:$(EXT_HDR)=-whitesmith$(EXT_HDR))


ASTYLE_BANNER    = --style=banner

SRC_FILES_SUFFIX_BANNER = $(SRC_FILES:$(EXT_SRC)=-banner$(EXT_SRC))

HDR_FILES_SUFFIX_BANNER = $(HDR_FILES:$(EXT_HDR)=-banner$(EXT_HDR))


ASTYLE_GNU  = --style=gnu

SRC_FILES_SUFFIX_GNU = $(SRC_FILES:$(EXT_SRC)=-gnu$(EXT_SRC))

HDR_FILES_SUFFIX_GNU = $(HDR_FILES:$(EXT_HDR)=-gnu$(EXT_HDR))


ASTYLE_GNU  = --style=linux

SRC_FILES_SUFFIX_LINUX = $(SRC_FILES:$(EXT_SRC)=-linux$(EXT_SRC))

HDR_FILES_SUFFIX_LINUX = $(HDR_FILES:$(EXT_HDR)=-linux$(EXT_HDR))


ASTYLE_HORSTMANN  = --style=horstmann

SRC_FILES_SUFFIX_HORSTMANN = $(SRC_FILES:$(EXT_SRC)=-horstmann$(EXT_SRC))

HDR_FILES_SUFFIX_HORSTMANN = $(HDR_FILES:$(EXT_HDR)=-horstmann$(EXT_HDR))

ASTYLE_LISP  = --style=lisp

SRC_FILES_SUFFIX_LISP = $(SRC_FILES:$(EXT_SRC)=-lisp$(EXT_SRC))

HDR_FILES_SUFFIX_LISP = $(HDR_FILES:$(EXT_HDR)=-lisp$(EXT_HDR))

ASTYLE_PICO  = --style=pico

SRC_FILES_SUFFIX_PICO = $(SRC_FILES:$(EXT_SRC)=-pico$(EXT_SRC))

HDR_FILES_SUFFIX_PICO = $(HDR_FILES:$(EXT_HDR)=-pico$(EXT_HDR))


ASTYLE_PYTHON  = --style=python

SRC_FILES_SUFFIX_PYTHON = $(SRC_FILES:$(EXT_SRC)=-python$(EXT_SRC))

HDR_FILES_SUFFIX_PYTHON = $(HDR_FILES:$(EXT_HDR)=-python$(EXT_HDR))




SRC_FILES_SUFFIX_USER = $(SRC_FILES:$(EXT_SRC)=-user$(EXT_SRC))

HDR_FILES_SUFFIX_USER = $(HDR_FILES:$(EXT_HDR)=-user$(EXT_HDR))


  ifeq ($(MAKECMDGOALS),astyle-ansi)
    FMT_SUFFIX_SRC=-ansi$(EXT_SRC)
    FMT_SUFFIX_HDR=-ansi$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-java)
    FMT_SUFFIX_SRC=-java$(EXT_SRC)
    FMT_SUFFIX_HDR=-java$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-kr)
    FMT_SUFFIX_SRC=-kr$(EXT_SRC)
    FMT_SUFFIX_HDR=-kr$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-stroustrup)
    FMT_SUFFIX_SRC=-stroustrup$(EXT_SRC)
    FMT_SUFFIX_HDR=-stroustrup$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-whitesmith)
    FMT_SUFFIX_SRC=-whitesmith$(EXT_SRC)
    FMT_SUFFIX_HDR=-whitesmith$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-banner)
    FMT_SUFFIX_SRC=-banner$(EXT_SRC)
    FMT_SUFFIX_HDR=-banner$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-gnu)
    FMT_SUFFIX_SRC=-gnu$(EXT_SRC)
    FMT_SUFFIX_HDR=-gnu$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-linux)
    FMT_SUFFIX_SRC=-linux$(EXT_SRC)
    FMT_SUFFIX_HDR=-linux$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-horstmann)
    FMT_SUFFIX_SRC=-horstmann$(EXT_SRC)
    FMT_SUFFIX_HDR=-horstmann$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-lisp)
    FMT_SUFFIX_SRC=-lisp$(EXT_SRC)
    FMT_SUFFIX_HDR=-lisp$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-pico)
    FMT_SUFFIX_SRC=-pico$(EXT_SRC)
    FMT_SUFFIX_HDR=-pico$(EXT_HDR)
  endif


  ifeq ($(MAKECMDGOALS),astyle-python)
    FMT_SUFFIX_SRC=-python$(EXT_SRC)
    FMT_SUFFIX_HDR=-python$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS),astyle-user)
    FMT_SUFFIX_SRC=-user$(EXT_SRC)
    FMT_SUFFIX_HDR=-user$(EXT_HDR)
  endif


#################### [END] indent tool variables [END] #########################



#################### [START] indent tool targets [START] #######################



ifeq ($(USE_TABS),F)
ASTYLE_USE_TABS = --convert-tabs  # Or empty
else
ASTYLE_USE_TABS =
endif



USE_SPACES = T

ifeq ($(USE_SPACES),T)
ASTYLE_INDENT = --indent=spaces=$(INDENTATION)
else
ASTYLE_INDENT = --indent=tab=$(INDENTATION)
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-ansi
astyle-ansi:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_ANSI) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_ANSI) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in ansi-style as: $(SRC_FILES_SUFFIX_ANSI)"
	@echo "Files formatted in ansi-style as: $(HDR_FILES_SUFFIX_ANSI)"
else
.PHONY: astyle-ansi
astyle-ansi:
	$(ASTYLE) --suffix=none $(ASTYLE_ANSI) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_ANSI) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-java
astyle-java:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_JAVA) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_JAVA) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in java-style as: $(SRC_FILES_SUFFIX_JAVA)"
	@echo "Files formatted in java-style as: $(HDR_FILES_SUFFIX_JAVA)"
else
.PHONY: astyle-java
astyle-java:
	$(ASTYLE) --suffix=none $(ASTYLE_JAVA) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_JAVA) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-kr
astyle-kr:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_KR) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_KR) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in kr-style as: $(SRC_FILES_SUFFIX_KR)"
	@echo "Files formatted in kr-style as: $(HDR_FILES_SUFFIX_KR)"
else
.PHONY: astyle-kr
astyle-kr:
	$(ASTYLE) --suffix=none $(ASTYLE_KR) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_KR) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-stroustrup
astyle-stroustrup:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_STROUSTRUP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_STROUSTRUP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in stroustrup-style as: $(SRC_FILES_SUFFIX_STROUSTRUP)"
	@echo "Files formatted in stroustrup-style as: $(HDR_FILES_SUFFIX_STROUSTRUP)"
else
.PHONY: astyle-stroustrup
astyle-stroustrup:
	$(ASTYLE) --suffix=none $(ASTYLE_STROUSTRUP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_STROUSTRUP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-whitesmith
astyle-whitesmith:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_WHITESMITH) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_WHITESMITH) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in whitesmith-style as: $(SRC_FILES_SUFFIX_WHITESMITH)"
	@echo "Files formatted in whitesmith-style as: $(HDR_FILES_SUFFIX_WHITESMITH)"
else
.PHONY: astyle-whitesmith
astyle-whitesmith:
	$(ASTYLE) --suffix=none $(ASTYLE_WHITESMITH) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_WHITESMITH) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-banner
astyle-banner:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_BANNER) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_BANNER) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in banner-style as: $(SRC_FILES_SUFFIX_BANNER)"
	@echo "Files formatted in banner-style as: $(HDR_FILES_SUFFIX_BANNER)"
else
.PHONY: astyle-banner
astyle-banner:
	$(ASTYLE) --suffix=none $(ASTYLE_BANNER) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_BANNER) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-gnu
astyle-gnu:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_GNU) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_GNU) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in gnu-style as: $(SRC_FILES_SUFFIX_GNU)"
	@echo "Files formatted in gnu-style as: $(HDR_FILES_SUFFIX_GNU)"
else
.PHONY: astyle-gnu
astyle-gnu:
	$(ASTYLE) --suffix=none $(ASTYLE_GNU) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_GNU) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-linux
astyle-linux:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_LINUX) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_LINUX) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in linux-style as: $(SRC_FILES_SUFFIX_LINUX)"
	@echo "Files formatted in linux-style as: $(HDR_FILES_SUFFIX_LINUX)"
else
.PHONY: astyle-linux
astyle-linux:
	$(ASTYLE) --suffix=none $(ASTYLE_LINUX) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_LINUX) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-horstmann
astyle-horstmann:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_HORSTMANN) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_HORSTMANN) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in horstmann-style as: $(SRC_FILES_SUFFIX_HORSTMANN)"
	@echo "Files formatted in horstmann-style as: $(HDR_FILES_SUFFIX_HORSTMANN)"
else
.PHONY: astyle-horstmann
astyle-horstmann:
	$(ASTYLE) --suffix=none $(ASTYLE_HORSTMANN) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_HORSTMANN) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-lisp
astyle-lisp:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_LISP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_LISP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in lisp-style as: $(SRC_FILES_SUFFIX_LISP)"
	@echo "Files formatted in lisp-style as: $(HDR_FILES_SUFFIX_LISP)"
else
.PHONY: astyle-lisp
astyle-lisp:
	$(ASTYLE) --suffix=none $(ASTYLE_LISP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_LISP) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-pico
astyle-pico:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_PICO) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_PICO) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo 'Code formatting done files overwritten'
else
.PHONY: astyle-pico
astyle-pico:
	$(ASTYLE) --suffix=none $(ASTYLE_PICO) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_PICO) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-python
astyle-python:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_PYTHON) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_PYTHON) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in python-style as: $(SRC_FILES_SUFFIX_PYTHON)"
	@echo "Files formatted in python-style as: $(HDR_FILES_SUFFIX_PYTHON)"
else
.PHONY: astyle-python
astyle-python:
	$(ASTYLE) --suffix=none $(ASTYLE_PYTHON) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_PYTHON) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: astyle-user
astyle-user:
	@for v in $(SRC_FILES) ; do $(ASTYLE) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(ASTYLE) $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) < "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in user-style as: $(SRC_FILES_SUFFIX_USER)"
	@echo "Files formatted in user-style as: $(HDR_FILES_SUFFIX_USER)"
else
.PHONY: astyle-user
astyle-user:
	$(ASTYLE) --suffix=none $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(ASTYLE_OPTS) $(SRC_FILES)  # Will format and overwrite your source files with making a backup file.
	$(ASTYLE) --suffix=none $(ASTYLE_USE_TABS) $(ASTYLE_INDENT) $(ASTYLE_OPTS) $(HDR_FILES)  # Will format and overwrite your source files with making a backup file.
	@echo "Code formatting done from $(ASTYLE). Files overwritten !"
endif


.PHONY: astyle-clean
astyle-clean:
	- $(RM) -f $(SRC_FILES_SUFFIX_KR) $(HDR_FILES_SUFFIX_KR) \
	           $(SRC_FILES_SUFFIX_GNU) $(HDR_FILES_SUFFIX_GNU) \
	           $(SRC_FILES_SUFFIX_ANSI) $(HDR_FILES_SUFFIX_ANSI) \
	           $(SRC_FILES_SUFFIX_LINUX) $(HDR_FILES_SUFFIX_LINUX) \
	           $(SRC_FILES_SUFFIX_JAVA) $(HDR_FILES_SUFFIX_JAVA) \
	           $(SRC_FILES_SUFFIX_STROUSTRUP) $(HDR_FILES_SUFFIX_STROUSTRUP) \
	           $(SRC_FILES_SUFFIX_WHITESMITH) $(HDR_FILES_SUFFIX_WHITESMITH) \
	           $(SRC_FILES_SUFFIX_BANNER) $(HDR_FILES_SUFFIX_BANNER) \
	           $(SRC_FILES_SUFFIX_HORSTMANN) $(HDR_FILES_SUFFIX_HORSTMANN) \
	           $(SRC_FILES_SUFFIX_LISP) $(HDR_FILES_SUFFIX_LISP) \
	           $(SRC_FILES_SUFFIX_PICO) $(HDR_FILES_SUFFIX_PICO) \
	           $(SRC_FILES_SUFFIX_PYTHON) $(HDR_FILES_SUFFIX_PYTHON)



else

$(warning Install the astyle package !!!)

endif

endif # USE_ASTYLE

#################### [END] astyle tool targets [END] ###########################


#################### [START] astyle tool variables [START] #####################

ifeq ($(USE_BCPP),T)

BCPP  = $(call BINARY_EXIST, bcpp)

ifneq ($(BCPP), )

SRC_FILES_SUFFIX_KR = $(SRC_FILES:$(EXT_SRC)=-kr$(EXT_SRC))
HDR_FILES_SUFFIX_KR = $(HDR_FILES:$(EXT_HDR)=-kr$(EXT_HDR))

SRC_FILES_SUFFIX_PASCAL = $(SRC_FILES:$(EXT_SRC)=-pascal$(EXT_SRC))
HDR_FILES_SUFFIX_PASCAL = $(HDR_FILES:$(EXT_HDR)=-pascal$(EXT_HDR))


  ifeq ($(MAKECMDGOALS), bcpp-kr)
    FMT_SUFFIX_SRC=-kr$(EXT_SRC)
    FMT_SUFFIX_HDR=-kr$(EXT_HDR)
  endif

  ifeq ($(MAKECMDGOALS), bcpp-pascal)
    FMT_SUFFIX_SRC=-pascal$(EXT_SRC)
    FMT_SUFFIX_HDR=-pascal$(EXT_HDR)
  endif


FUNC_SPACING = 2

BCPP_OPTS =

BCPP_OPTS += -f $(FUNC_SPACING)

ifeq ($(USE_TABS),T)
BCPP_OPTS += -t # tabs
endif
ifeq ($(USE_TABS),F)
BCPP_OPTS += -s # spaces
endif

BCPP_OPTS += -i $(INDENTATION)

BCPP_OPTS += -ylcnc # (Turn on Leave_Comments_NoCode)

BCPP_OPTS += -na # (Do not remove non-ASCII characters)

#BCPP_BRACE_ON_NEW_LINE = on

#ifeq $($(BCPP_BRACE_ON_NEW_LINE),on)
#BCPP_OPTS += -bnl
#else
#BCPP_OPTS += -bcl
#endif

#BCPP_BACKUP_FILE = yes

#ifeq $($(BCPP_BACKUP_FILE),yes)
#BCPP_OPTS += -yb
#else
#BCPP_OPTS += -nb

ifneq ($(OVERWRITE),T)
.PHONY: bcpp-kr
bcpp-kr:
	@for v in $(SRC_FILES) ; do $(BCPP) -bnl -yo -nb $(BCPP_OPTS) -fi "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(BCPP) -bnl -yo -nb $(BCPP_OPTS) -fi "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_HDR) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in kr-style as: $(SRC_FILES_SUFFIX_KR)"
	@echo "Files formatted in kr-style as: $(HDR_FILES_SUFFIX_KR)"
else
.PHONY: bcpp-kr
bcpp-kr:
	@for v in $(SRC_FILES) ; do $(BCPP) -bnl -no -nb $(BCPP_OPTS) -fi "$${v}" ;  done ;
	@echo "Code formatting done from $(BCPP). Files overwritten !"
endif

ifneq ($(OVERWRITE),T)
.PHONY: bcpp-pascal
bcpp-pascal:
	@for v in $(SRC_FILES) ; do $(BCPP) -bcl -yo -nb $(BCPP_OPTS) -fi "$${v}" > "$$(dirname $$v)/$$(basename -s $(EXT_SRC) $$v)"$(FMT_SUFFIX_SRC)  ;  done ;
	@for v in $(HDR_FILES) ; do $(BCPP) -bcl -yo -nb $(BCPP_OPTS) -fi "$${v}" > "$$(dirname $$v)/$$(basename -s $(HDR_SRC) $$v)"$(FMT_SUFFIX_HDR)  ;  done ;
	@echo "Files formatted in pascal-style as: $(SRC_FILES_SUFFIX_KR)"
	@echo "Files formatted in pascal-style as: $(HDR_FILES_SUFFIX_KR)"
else
.PHONY: bcpp-pascal
bcpp-pascal:
	@for v in $(SRC_FILES) ; do $(BCPP) -bcl -no -nb $(BCPP_OPTS) -fi "$${v}" ;  done ;
	@echo "Code formatting done from $(BCPP). Files overwritten !"
endif

.PHONY: bcpp-clean
bcpp-clean:
	- $(RM) -f $(SRC_FILES_SUFFIX_KR) $(HDR_FILES_SUFFIX_KR) \
	           $(SRC_FILES_SUFFIX_PASCAL) $(HDR_FILES_SUFFIX_PASCAL)



else

$(warning Install the bcpp package !!!)

endif

endif # USE_BCPP
