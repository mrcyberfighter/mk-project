#  Make invocation
#
#  Make -f [--file ] filename -q [--question] -n [--just-print] ...
#

# Introduction:
#
# They are 2 sort of Makefile (i Think)
# 1. They for making you the life easier.
# 2. They for distributing stuff (see automake from the autotools or cmake).
#

####### Variables. #######
#
# $@  Target filename with extension
# $%  Target meber name if the target is an archive member.
# $<  First dependencies in first rule.
# $?  List of all dependencies newer than the target.
# $^  List of all dependencies without repetition.
# $+  List of all dependencies with repetition.
# $*  The steam which match implicit rules.



####### Assigments #######
# define var     value  # Value definition (used for multiline).
# define var =   value  # indirect. (the value change at the next assignment for the final variable value.)
# define var :=  value  # direct.   (the value doesn't change at the next assignment for the final variable value.)
# define var ::= value  # retro and inter compatibility with other make tools.
# define var +=  value  # incr   assigment operator.
# define var ?=  value  # ifndef assigment operator.

# endif # End of a definition.

# target : dependencies    # target can be a target name or a file...
# \t RULE                  # dependencies can be files to update.
#                          # starting with a tab or whatever define in the .RECIPEPREFIX built-in variables.



# CC        is defined per default as the system c-compiler.
# CXX       is defined per default as the system c++-compiler.
#
# CFLAGS    isn't defined per default.  # By distributing think about that the user can overwrite it.
# CXXFLAGS  isn't defined per default.  # By distributing think about that the user can overwrite it.
# CPPFLAGS  isn't defined per default.  # By distributing think about that the user can overwrite it.
#
# LDFLAGS   ins't defined per default.  # By distributing think about that the user can overwrite it,
# LDLIBS    isn't defined per default   # but should if he desn't fork the project with additional.



# --no-print-directory -> I dislike directory printing behaviour of make: it look's like an error message cause of formatting --print-directory...
# -j       -> This enable the job option the compilation will be faster because it start a job for command simultaneous.
# -j [int] -> You can add an integer to limit the number of jobs you want. 4 jobs is good.
# -O [target|line|recurse|none] -> Type of output synchronizing by using jobs
MAKE_OPTS = %s

MAKEFLAGS += $(MAKE_OPTS)

SHELL = %s

################################################################################

include ./.SubMakefiles/binary_checks.mk

include ./.SubMakefiles/path.mk

################################################################################

# Programming language choosen by the user.
LANG = python   

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_SRC = .py

EXT_HDR = .py

INTERPRETER = $(call BINARY_EXIST, %s)


#################### Program informations. #####################################

BIN_DIR = ./bin

PRGNAME = %s

VERSION = %s

################################################################################

SRC_DIR  = ./source

SRC_FILE = %s

PRGPATH = $(SRC_DIR)/$(SRC_FILE)

################################################################################

SRC_FILES = $(SRC_DIR)/%s

HDR_FILES =

################################################################################

#NOTE: not GNU make tools have less capabilitites than the original tool.
ifneq ($(notdir $(MAKE)),make)
$(warning You don't use the GNU make tool: this can go into incompatiblities with this Makefile)
endif

# The default or all target is the default target (wenn you only enter $ make) or the first target encounter in the Makefile.
# First target appearing is the implicte variable: .DEFAULT: target.
all:
	@ $(MAKE) set_x
	$(INTERPRETER) $(PRGPATH)

.PHONY: $(BIN_DIR)
$(BIN_DIR):
	- @if `test ! -d $(BIN_DIR)` ; then  $(MKDIR_P) $(BIN_DIR) ; fi

.PHONY: set_x
set_x:
	@ if `test ! -x $(PRGPATH)` ; then $(CHMOD) u+x $(PRGPATH) ; fi

#################### [START] Debugging targets [START] #########################

# .PHONY: targets are run everytime you call it with:
# $ make phony_target
.PHONY: fdebug ddebug gdebug gdb

# File debug.
fdebug:
	- $(RM) -f ./debug.txt
	$(MAKE) all 2> ./debug.txt


# Launch interactive pdb (python debugger).
pdb:
	$(INTERPRETER) -m pdb $(PRGPATH)

#################### [END] Debugging targets [END] #############################



#################### [START] gettext support [START] ###########################


ifneq ($(XGETTEXT), )
XGETTEXT_OPTS = -L C --keyword=_ --keyword=N_ --from-code=UTF-8
.PHONY: xgettext
xgettext:
	$(XGETTEXT) $(XGETTEXT_OPTS) $(SRC_FILES)
	$(MV) messages.po $(PRGNAME).pot
endif

lang=


ifneq ($(MSGFMT), )
MSGFMT_OPTS = -v -f
.PHONY: msgfmt
msgfmt:
ifneq ($(lang), )
	$(MSGFMT) $(MSGFMT_OPTS) $(PRGNAME).pot -o $(PRGNAME).mo
	if `test ! -d $(LOCALE_DIR)/$(lang)/LC_MESSAGES` ; then $(MKDIR_P) $(LOCALE_DIR)/$(lang)/LC_MESSAGES ; fi
	if `test ! -d $(LOCALE_DIR)/$(lang)/LC_MESSAGES` ; then $(MKDIR_P) $(LOCALE_DIR)/$(lang)/LC_MESSAGES ; fi
	if `test ! -d $(GETTEXT_BKUP_DIR)/$(lang)` ;       then $(MKDIR_P) $(GETTEXT_BKUP_DIR)/$(lang)       ; fi
	$(CP) $(PRGNAME).pot $(GETTEXT_BKUP_DIR)/$(lang)/
	$(MV) $(PRGNAME).mo $(LOCALE_DIR)/$(lang)/LC_MESSAGES
	@echo
	@echo "Now you can try your translation"
	@echo "by setting the value of the \$$LANGUAGE variable:"
	@echo "$$ export LANGUAGE=fr:en      # Language on French with English fallback."
	@echo "$$ export set LANGUAGE=fr:en  # Language on French with English fallback."
	@echo "$$ declare LANGUAGE=fr:en     # Language on French with English fallback."
else
	@echo  "You must define the lang variable on the commandline."
	@echo  "Per example \"make msgfmt lang=fr\" for french."
endif

endif


ifneq ($(MSGUNIQ), )
.PHONY: msguniq
MSGUNIQ_OPTS=
msguniq:
	if `test -f $(PRGNAME).pot` ; then $(MSGUNIQ) $(MSGUNIQ_OPTS) $(PRGNAME).pot -o $(PRGNAME).pot ; fi
endif


################################################################################


#################### [START] program analyze tools targets [START] #############

ifneq ($(STRACE), )
.PHONY: strace
# Edit the wanted options to give to strace program.
STRACE_OPTS =
strace:
	$(STRACE) $(STRACE_OPTS) $(INTERPRETER) $(PRGPATH)
endif

ifneq ($(LTRACE), )
.PHONY: ltrace
# Edit the wanted options to give to ltrace program.
LTRACE_OPTS =
ltrace:
	$(LTRACE) $(STRACE_OPTS) $(INTERPRETER) $(PRGPATH)
endif

ifneq ($(HEXDUMP), )
# Edit the wanted options to give to hexdump program.
HEXDUMP_OPTS =
.PHONY: hexdump
hexdump:
	$(HEXDUMP) $(HEXDUMP_OPTS) $(PRGPATH)
endif

ifneq ($(DIFF), )
# Edit the wanted options to give to diff program.
# -q -y  -t --suppress-blank-empty --suppress-common-lines --show-c-function
DIFF_OPTS =
.PHONY: diff
diff:
	$(DIFF) $(DIFF_OPTS) "$(argv)"
endif

#### [END] program analyze tools targets [END] ####




include ./.SubMakefiles/code_formatter.mk

include ./.SubMakefiles/documentation.mk

include ./.SubMakefiles/distributing.mk



#### [START] cleaning targets [START] ####

.PHONY: clean_save clean_doc clean_doc_gen

clean_prg:
	- $(RM) -f $(PRGPATH)

ifneq ($(FIND), )
.PHONY: clean_save
clean_save:
	$(FIND) . -iregex .*~$$ -exec rm -f {} \;
endif

.PHONY: clean_doc
clean_doc:
	- $(RM) -f $(INFO_FILE) $(TEXT_FILE) $(PDF_FILE) $(HTML_FILE) $(HTML5_FILE) $(TEXI_FILE) $(ODT_FILE) $(XML_FILE) $(LATEX_FILE) $(ASCIIDOC_FILE) $(EPUB_FILE)

.PHONY: clean_doc_gen
clean_doc_gen:
	- $(RM) -f $(TEXI_FILE) $(TEXI_MAN_FILE) $(TEXI_INFO_FILE) $(TEXI_PDF_FILE) $(TEXI_HTML_FILE) $(TEXI_HTML5_FILE) $(TEXI_ODT_FILE) $(TEXI_XML_FILE) $(TEXI_LATEX_FILE) $(TEXI_ASCIIDOC_FILE) $(TEXI_EPUB_FILE) $(TEXI_PLAIN_FILE) \
	                        $(RST_MAN_FILE)  $(RST_INFO_FILE)  $(RST_PDF_FILE)  $(RST_HTML_FILE)  $(RST_HTML5_FILE)  $(RST_ODT_FILE)  $(RST_XML_FILE)  $(RST_LATEX_FILE)  $(RST_ASCIIDOC_FILE)  $(RST_EPUB_FILE)  $(RST_PLAIN_FILE) \
	                        $(MD_MAN_FILE)   $(MD_INFO_FILE)   $(MD_PDF_FILE)   $(MD_HTML_FILE)   $(MD_HTML5_FILE)   $(MD_ODT_FILE)   $(MD_XML_FILE)   $(MD_LATEX_FILE)   $(MD_ASCIIDOC_FILE)   $(MD_EPUB_FILE)   $(MD_PLAIN_FILE)


clean:

#### [END] cleaning targets [END] ####


#### [START] utilities targets [START] ####

.PHONY: info exec search-pattern




ifneq ($(FIND), )
.PHONY: list-project
list-project:
	$(FIND) * -exec file {} \;
endif

# Put the informatuons you need in this target.
info:
	@echo
	@ls -l $(PRGPATH) ; # Must make a personnal tool displaying file size in K but with the comma rest.
	@echo
ifneq ($(FILE), )
	@file $(PRGPATH)  ;
	@echo
endif
	@ls -s -h $(PRGPATH) ;
	@echo

# Overwrite on the cmdline or set it in Makefile if your program need some args.
# or call make by defining this variable:
# $ make argv="foo bar" exec

exec:
	@ $(MAKE) set_x
	$(INTERPRETER) $(PRGPATH) $(argv)

ifneq ($(GREP), )
search-pattern:
	$(GREP) -r -n --color auto "$(argv)"
endif

ifneq ($(FIND), )
rm-trailing-spaces:
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_SRC) -exec sed -i 's/[[:space:]]$$//' {} \;
endif

.PHONY: prepend-license
prepend-license:
	@python ../scripts∕prepend_license.py -d $(SRC_DIR) -f $(BOILERPLATE) -l $(LANG)


#### [END] utilities targets [END] ####

#################### Test (un)install: to customize (experimental). ############

.PHONY: desktop test-install test-uninstall

# it were good to use a tool like xdg-desktop-icon or desktop-file-install for installing the *.desktop file.
desktop:
	@echo "[Desktop Entry]"  > $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Name=$(PRGNAME)"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Version=$(VERSION)"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "GenericName=$(PRGNAME)"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Comment=" >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Exec=$(PRGNAME)"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Icon=$(pkgdatadir)/..."  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Terminal=false"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "X-MultipleArgs=false"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "StartupNotify=true"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Type=Application"  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "MimeType="  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Keywords="  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
	@echo "Categories="  >> $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
#	xdg-desktop-icon install $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
#	desktop-file-install --rebuild-mime-info-cache $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop

test-install:
# To execute as root.
# Make directory if not available:
	if `test ! -d $(DESTDIR)$(prefix)/share/$(PRGNAME)` ; then $(MKDIR_P) $(DESTDIR)$(prefix)/share/$(PRGNAME) ; fi
# Copy all files in ./share:
	$(CP_R) ./share/* $(DESTDIR)$(prefix)/share/
# For special requirement like this:
#	$(CHMOD) -R a+rx $(DESTDIR)$(prefix)/share/$(PRGNAME)
#	$(CHMOD) -R a+rwx $(DESTDIR)$(prefix)/share/$(PRGNAME)/configuration
	$(INSTALL_PROGRAM) $(PRGPATH) $(DESTDIR)$(bindir)/$(PRGNAME).py
	$(LN_S) $(DESTDIR)$(bindir)/$(PRGNAME).py $(DESTDIR)$(bindir)/$(PRGNAME)
	$(MAKE) desktop

test-uninstall:
# To execute as root.
# Remove all dependencies files:
	- if `test -d $(DESTDIR)$(prefix)/share/$(PRGNAME)` ; then $(RM_R) -f $(DESTDIR)$(prefix)/share/$(PRGNAME) ; fi
# Remove the binary
	- if `test -f $(DESTDIR)$(bindir)/$(PRGNAME)` ; then $(RM) $(DESTDIR)$(bindir)/$(PRGNAME) ; fi
# Remove translation files
#	- $(RM) -f $(prefix)/share/locale/(fr)/LC_MESSAGES/$(PRGNAME).mo
	- $(RM) -f $(DESKTOP_DIR)/$(PRGNAME).desktop

################################################################################

#### [START] print available targets [START] #####

.PHONY: help

help:
	@echo "make        # Launch the python script."
	@echo "make exec   # Launch the python script."
	@echo
	@echo "make pdb    # Launch pdb with the python file given as argument."
	@echo "make fdebug # File debug: redirect output to ./debug.txt file"
	@echo
ifneq ($(HEXDUMP), )
	@echo "make hexdump    # Process a hexdump on the python script."
endif
	@echo
	@echo "make info       # Print python script file informations."
	@echo
	@echo "make clean_doc  # Remove all documenation files."
ifneq ($(FIND), )
	@echo "make clean_save # Remove all backup files."
endif
	@echo
ifneq ($(GREP), )
	@echo "make search-pattern argv=pattern # Search for pattern in source files."
endif
ifneq ($(FIND), )
	@echo
	@echo "make rm-trailing-spaces # Remove trailing spaces from files."
endif
	@echo
	@echo "make prepend-license    # Prepend license to all source files."
	@echo
ifneq ($(DIFF), )
	@echo "make diff argv=file1 file2 # Make a diff between the given files."
	@echo
endif
ifneq ($(XGETTEXT), )
	@echo "make xgettext           # Generate a *.pot file from source files."
endif
ifneq ($(MSGFMT), )
	@echo "make msgfmt lang=[LANG] # Generate a *.mo file and set it into locale directory"
endif
ifneq ($(MSGUNIQ), )
	@echo "make msguniq            # Remove duplicate in a translation file (*.po, *.pot)"
	@echo
endif
ifeq ($(USE_TEXI),T)
ifneq ($(MAKEINFO), )
	@echo "make texi2info   # Make info  doc file from *.texi file."
	@echo "make texi2html   # Make html  doc file from *.texi file."
	@echo "make texi2xml    # Make xml   doc file from *.texi file."
ifneq ($(TEXI2DVI), )
	@echo "make texidvi2pdf # Make pdf   doc file from *.texi file."
endif
endif
ifneq ($(PANDOC), )
	@echo "make texi2html5  # Make html5 doc file from *.texi file."
	@echo "make texi2pdf    # Make pdf   doc file from *.texi file."
	@echo "make texi2man    # Make man   doc file from *.texi file."
	@echo "make texi2odt    # Make odt   doc file from *.texi file."
	@echo "make texi2latex  # Make latex doc file from *.texi file."
	@echo "make texi2plain  # Make plain doc file from *.texi file."
	@echo "make texi2epub   # Make epub  doc file from *.texi file."
	@echo
endif
endif # USE_TEXI
	@echo
ifeq ($(USE_RST),T)
ifneq ($(RST2HTML), )
	@echo "make rst2html  # Make html  doc file from *.rst file."
endif
ifneq ($(RST2PDF), )
	@echo "make rst2pdf   # Make pdf   doc file from *.rst file."
endif
ifneq ($(RST2MAN), )
	@echo "make rst2man   # Make man   doc file from *.rst file."
endif
ifneq ($(RST2ODT), )
	@echo "make rst2odt   # Make man   doc file from *.rst file."
endif
ifneq ($(RST2XML), )
	@echo "make rst2xml   # Make xml   doc file from *.rst file."
endif
ifneq ($(RST2LATEX), )
	@echo "make rst2latex # Make latex doc file from *.rst file."
endif
ifneq ($(PANDOC), )
	@echo "make rst2html5 # Make html5 doc file from *.rst file."
	@echo "make rst2epub  # Make epub  doc file from *.rst file."
	@echo "make rst2info  # Make info  doc file from *.rst file."
	@echo "make rst2plain # Make plain doc file from *.rst file."
endif
endif # USE_RST
	@echo
ifeq ($(USE_MD),T)
ifneq ($(PANDOC), )
	@echo "make md2html   # Make html  doc file from *.md file."
	@echo "make md2html5  # Make html5 doc file from *.md file."
	@echo "make md2pdf    # Make pdf   doc file from *.md file."
	@echo "make md2man    # Make man   doc file from *.md file."
	@echo "make md2odt    # Make odt   doc file from *.md file."
	@echo "make md2xml    # Make xml   doc file from *.md file."
	@echo "make md2latex  # Make latex doc file from *.md file."
	@echo "make md2epub   # Make epub  doc file from *.md file."
	@echo "make md2info   # Make info  doc file from *.md file."
	@echo "make md2plain  # Make plain doc file from *.md file."
endif
endif # USE_MD
	@echo
ifneq ($(INFO), )
	@echo "make show-info # Display info documentation."
endif
ifneq ($(MAN), )
	@echo "make show-man  # Display man documentation."
endif
ifneq ($(BROWSER), )
	@echo "make show-html # Display html documentation."
	@echo "make show-xml  # Display xml  documentation."
endif
ifneq ($(PDF), )
	@echo "make show-pdf  # Display pdf  documentation."
endif
ifneq ($(ODT), )
	@echo "make show-odt  # Display odt  documentation."
endif
ifneq ($(EPUB), )
	@echo "make show-epub # Display epub documenation."
endif
	@echo
ifneq ($(STRACE), )
	@echo "make strace    # trace the python script."
endif
ifneq ($(LTRACE), )
	@echo "make ltrace    # ltrace the python script."
endif
ifeq ($(USE_PINDENT),T)
ifeq ($(PINDENT),T)
	@echo
	@echo "make pindent      # Use pindent to format source code"
endif
endif
	@echo
ifneq ($(TAR), )
	@echo "make dist-tar     # Generate a tar archive from the project."
ifneq ($(GZ), )
	@echo "make dist-tar-gz  # Generate a tar.gz archive from the project."
endif
ifneq ($(BZ2), )
	@echo "make dist-tar-bz2 # Generate a tar.bz2 archive from the project."
endif
endif
ifneq ($(ZIP), )
	@echo "make dist-zip     # Generate a zip archive from the project."
endif
	@echo
	@echo "make help         # Display all available targets."
#### [END] print available targets [END] #####