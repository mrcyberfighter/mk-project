# Copyright (c)  2016,2017  Brüggemann Eddie.
# Permission is granted to copy, distribute and/or modify this document
# under the terms of the GNU Free Documentation License, Version 1.3
# or any later version published by the Free Software Foundation;
# with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
# A copy of the license is included in the section entitled "GNU
# Free Documentation License".


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
# $% Target member name if the target is an archive member.
# $<  First dependencies in first rule.
# $?  List of all dependencies newer than the target.
# $^  List of all dependencies without repetition.
# $+  List of all dependencies with repetition.
# $*  The steam which match implicit rules.



####### Assignments #######
# define var     value  # Value definition (used for multi-line).
# define var =   value  # indirect. (the value change at the next assignment for the final variable value.)
# define var :=  value  # direct.   (the value doesn't change at the next assignment for the final variable value.)
# define var ::= value  # retro and inter compatibility with other make tools.
# define var +=  value  # incr   assignment operator.
# define var ?=  value  # shell expand assignment operator.

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
# LDFLAGS   isn't defined per default.  # By distributing think about that the user can overwrite it,
# LDLIBS    isn't defined per default   # but should if he doesn't fork the project with additional.

# .PHONY: targets are run every time you call it with:
# $ make phony_target

# --no-print-directory -> I dislike directory printing behavior of make: it looks like an error message cause of formatting --print-directory...
# -j       -> This enable the job option the compilation will be faster because it start a job for command simultaneous.
# -j [int] -> You can add an integer to limit the number of jobs you want. 4 jobs is good.
# -O [target|line|recurse|none] -> Type of output synchronizing by using jobs.
MAKE_OPTS = --no-print-directory # -j 2

MAKEFLAGS += $(MAKE_OPTS)

SHELL = /bin/bash

################################################################################

#################### [Start] functions [Start] #################################

# Define a function to check the presence of an executable through his binary path.
BINARY_CHECK = $(shell which $1 2> /dev/null)

BINARY_EXIST = $(if $(call BINARY_CHECK, $1 ), $(call BINARY_CHECK, $1 ))

# Define a function to check if a file exist.
FILE_EXIST   = $(if `test -f $1`,T,F)

# Define a function for library detection.
PKG_CONFIG_EXIST =  $(if `pkg-config --exists $1`,T,F)

################################################################################


############### [START] Check GNU make tool purpose [START] ####################

# NOTE: Use the defined $(MAKE) variable for calling the make tool in recipes.

MAKE    = $(call BINARY_EXIST, make)

############### [END] Check GNU make tool purpose [END] ########################

############### [START] Check coreutils tools [START] ##########################

MKDIR   = $(call BINARY_EXIST, mkdir)

MKDIR_P = $(MKDIR) -p

BASENAME = $(call BINARY_EXIST, basename)

LS = $(call BINARY_EXIST, ls)

LS_SIZE = $(LS) -s -h

CP = $(call BINARY_EXIST, cp)

CP_R = $(CP) -R

RM = $(call BINARY_EXIST, rm)

RM_R = $(RM) -R

MV  =  $(call BINARY_EXIST, mv)

CHMOD = $(call BINARY_EXIST, chmod)

TOUCH = $(call BINARY_EXIST, touch)

CD = $(call BINARY_EXIST, cd)

LN = $(call BINARY_EXIST, ln)

# @NOTE the -T option from the ln command is not portable on UNIX ln.
LN_S = $(LN) -s

ifeq ($(MKDIR), )
$(error Install the coreutils !!!)
endif

############### [END] Check coreutils tools [END] ##############################


########## [START] installation variables [START] ##############################

INSTALL  = $(call BINARY_EXIST, install)

INSTALL_PROGRAM = ${INSTALL} -c
INSTALL_DATA    = ${INSTALL} -c -m 644
INSTALL_DATA_RW = ${INSTALL} -c -m 666

DESTDIR =

################################################################################

#################### [Start] Other needed binaries [Start] #####################

# Install the findutils package if missing.
FIND = $(call BINARY_EXIST, find)

# Install the file package if missing.
FILE = $(call BINARY_EXIST, file)

# Package ???
SIZE = $(call BINARY_EXIST, size)

# Package ???
STRIP = $(call BINARY_EXIST, strip)

# Package ???
GREP  = $(call BINARY_EXIST, grep)

# Package ???
SED = $(call BINARY_EXIST, sed)

# Package ???
HEXDUMP = $(call BINARY_EXIST, hexdump)

# Install the install-info package if missing.
INSTALL_INFO = $(call BINARY_EXIST, install-info)

#################### [End] Other needed binaries [End] #########################



#################### [START] gettext support binaries [START] ##################

XGETTEXT = $(call BINARY_EXIST, xgettext)

MSGFMT = $(call BINARY_EXIST, msgfmt)

MSGUNIQ = $(call BINARY_EXIST, msguniq)

################################################################################

#################### [START] script language interpreters [START] ##############

PYTHON = $(call BINARY_EXIST, python2)

ifneq ($(PYTHON), )
PYTHON = $(call BINARY_EXIST, python)
endif

ifneq ($(PYTHON), )
PYTHON = $(call BINARY_EXIST, python3)
endif

#################### [START] Check documentation tools [START] #################

### Documentation viewer checks ###

XDG_OPEN = $(call BINARY_EXIST, xdg-open)

INFO = $(call BINARY_EXIST, info)

MAN  = $(call BINARY_EXIST, man)

BROWSER = $(call BINARY_EXIST, firefox)

ifeq ($(BROWSER), )
BROWSER = $(call BINARY_EXIST, chromium-browser)
endif

ifeq ($(BROWSER), )
BROWSER = $(call BINARY_EXIST, konqueror)
endif


ODT = $(call BINARY_EXIST, libreoffice)


PDF = $(call BINARY_EXIST, evince)

ifeq ($(PDF), )
PDF = $(call BINARY_EXIST, xpdf)
endif

ifeq ($(PDF), )
PDF = $(call BINARY_EXIST, mupdf)
endif

ifeq ($(PDF), )
PDF = $(call BINARY_EXIST, pdfcube)
endif

ifeq ($(PDF), )
PDF = $(call BINARY_EXIST, pdf-viewer)
endif

EPUB = $(call BINARY_EXIST, fbreader)

ifeq ($(EPUB), )
EPUB = $(call BINARY_EXIST, okular)
endif



# Rescue case for unfounded programs:
ifneq ($(XDG_OPEN), )

ifeq ($(BROWSER), )
BROWSER = $(XDG_OPEN)
endif

ifeq ($(PDF), )
PDF = $(XDG_OPEN)
endif

ifeq ($(ODT), )
ODT = $(XDG_OPEN)
endif

ifeq ($(EPUB), )
EPUB = $(XDG_OPEN)
endif


ifeq ($(INFO), )
INFO = $(XDG_OPEN)
endif


ifeq ($(MAN), )
MAN = $(XDG_OPEN)
endif

endif


#################### [END] Check documentation tools [END] #####################



#################### [START] Check debugging and profiling tools [START] #######
# DEBUGGING AND PROFILING programs and settings

# gprof binary check.
GPROF  = $(call BINARY_EXIST, gprof)

# nm binary check.
# nm: display symbols of an object file or a program (named a.out) per default.
NM      = $(call BINARY_EXIST, nm)


# readelf binary check.
# readelf: display informations about a program (a ELF (Executable Linkable Format) binary).
# READELF = $(call BINARY_EXIST, readelf) # No more used not portable.

# strace binary check.
# strace: Intercepts  and  records  the  system  calls  which are called by a
#         process and the signals which are received by a process.
STRACE  = $(call BINARY_EXIST, strace)


# ltrace binary check.
# ltrace: Trace library calls of a given program.
LTRACE  = $(call BINARY_EXIST, ltrace)


# objdump binary check.
# objdump: Display the informations about the object file(s).
OBJDUMP = $(call BINARY_EXIST, objdump)

# ldd: ldd  print the  shared  libraries  required by each program or shared
#      library specified on the command line.
#
# NOTE: A  safer alternative when dealing with untrusted executables is:
# $ objdump -p /path/to/program | grep NEEDED
LDD = $(call BINARY_EXIST, ldd)


# diff: diff print difference between 2 or more files
#
#
# NOTE: diff can work recursively on a folder.
# SUGGEST: the kompare diff-gui program.
DIFF = $(call BINARY_EXIST, diff)

# valgrind: debugging and dynamic analysing tools
#
VALGRIND = $(call BINARY_EXIST, valgrind)

ifeq ($(OBJDUMP), )
$(error Install the binutils package !)
endif

#################### [Start] Oprofile (prior to 1.0) binaries [START@ ##########

OPCONTROL = $(call BINARY_EXIST, opcontrol)

OPREPORT  = $(call BINARY_EXIST, opreport)

OPANNOTATE = $(call BINARY_EXIST, opannotate)

OPGPROF = $(call BINARY_EXIST, opgprof)

OCOUNT  = $(call BINARY_EXIST, ocount)

OPERF   = $(call BINARY_EXIST, operf)

OPARCHIVE = $(call BINARY_EXIST, oparchive)

#################### [END] Oprofile binarires [END] ############################

#################### [START] archiving and compressing utilities [START] #######

ZIP     = $(call BINARY_EXIST, zip)

TAR     = $(call BINARY_EXIST, tar)

GZ      = $(call BINARY_EXIST, gzip)

BZ2     = $(call BINARY_EXIST, bzip2)

LZMA    = $(call BINARY_EXIST, lzma)

XZ      = $(call BINARY_EXIST, xz)

RAR     = $(call BINARY_EXIST, rar)

LZOP    = $(call BINARY_EXIST, lzop)

LZIP    = $(call BINARY_EXIST, lzip)

UNZIP   = $(call BINARY_EXIST, unzip)

UNRAR   = $(call BINARY_EXIST, unrar)

#################### [END] archiving and compressing utilities [END] ###########

########## [START] directory variables [START] #################################

prefix = /usr/local

exec_prefix = $(prefix)

bindir  = $(prefix)/bin

sbindir = $(prefix)/sbin

libexecdir = $(exec_prefix)/libexec

datarootdir = $(prefix)/share

datadir     = $(datarootdir)

sysconfdir = $(prefix)/etc

sharedstatedir = $(prefix)/com

localstatedir = $(prefix)/var

includedir   = $(prefix)/include

oldincludedir = /usr/include

docdir = $(datarootdir)/doc

infodir = $(datarootdir)/info

htmldir = $(docdir)

dvidir = $(docdir)

pdfdir = $(docdir)

psdir = $(docdir)

libdir  = $(exec_prefix)/lib

lispdir =$(datarootdir)/emacs/site-lisp

localedir = $(datarootdir)/locale

mandir  = $(datarootdir)/man

man1dir = $(mandir)/man1

man2dir = $(mandir)/man2

man3dir = $(mandir)/man3

man4dir = $(mandir)/man4

man5dir = $(mandir)/man5

man6dir = $(mandir)/man6

man7dir = $(mandir)/man7

man7dir = $(mandir)/man8

man9dir = $(mandir)/man9


################################################################################

pkgdatadir      = $(datarootdir)/$(PRGNAME)

pkgincludedir   = $(includedir)/$(PRGNAME)

pkglibdir       = $(libdir)/$(PRGNAME)

pkglibexecdir   = $(libexecdir)/$(PRGNAME)

################################################################################

srcdir  = .

################################################################################

TMP_DIR   = /tmp

LOCALE_DIR = ./share/locale

GETTEXT_BKUP_DIR = ./gettext_backup

DESKTOP_DIR = /usr/share/applications

################################################################################

PREPEND_LICENSE_SCRIPT = ./.scripts/prepend_license.py

################################################################################

BOILERPLATE_PATH = ./.licensing/licensing.tmpl

############# [Start] temporary docbook file [START] ###########################

TMP_DBK_FILE = $(TMP_DIR)/mk-project_doc.dbk

################################################################################

############# [START] Documenation informations [START] ########################

DOC_DIR    = ./doc

SPHINX_OUTPUT_DIR = $(DOC_DIR)/build

RST_DIR    = $(DOC_DIR)/rst

MD_DIR     = $(DOC_DIR)/md

INFO_DIR   = $(DOC_DIR)/info

PDF_DIR    = $(DOC_DIR)/pdf

HTML_DIR   = $(DOC_DIR)/html

HTML5_DIR  = $(DOC_DIR)/html5

TEXT_DIR   = $(DOC_DIR)/text

MAN_DIR    = $(DOC_DIR)/man

ODT_DIR    = $(DOC_DIR)/odt

XML_DIR    = $(DOC_DIR)/xml

LATEX_DIR  = $(DOC_DIR)/latex

EPUB_DIR   = $(DOC_DIR)/epub

ASCIIDOC_DIR  = $(DOC_DIR)/asciidoc

#################### [START] Textinfo files [START] ################################

ifeq ($(USE_SPHINX),T)

SPHINX_TEXI_FILE = $(SPHINX_OUTPUT_DIR)/texinfo/$(PRGNAME).texi

SPHINX_MAN_FILE = $(SPHINX_OUTPUT_DIR)/man/$(PRGNAME).1

SPHINX_INFO_FILE = $(SPHINX_OUTPUT_DIR)/texinfo/$(PRGNAME).info

SPHINX_LATEX_FILE = $(SPHINX_OUTPUT_DIR)/latex/$(PRGNAME).tex

SPHINX_LATEX_PDF_FILE = $(SPHINX_OUTPUT_DIR)/latexpdf/$(PRGNAME).pdf

SPHINX_LATEXPDFJA_FILE = $(SPHINX_OUTPUT_DIR)/latexpdfja/$(PRGNAME).pdf

SPHINX_HTML_FILE = $(SPHINX_OUTPUT_DIR)/html/index.pdf

SPHINX_DIRHTML_FILE = $(SPHINX_OUTPUT_DIR)/dirhtml/index.pdf

SPHINX_SINGLEHTML_FILE = $(SPHINX_OUTPUT_DIR)/singlehtml/index.pdf

SPHINX_TEXINFO_FILE = $(SPHINX_OUTPUT_DIR)/texinfo/$(PRGNAME).texinfo

SPHINX_XML_FILE = $(SPHINX_OUTPUT_DIR)/xml/$(PRGNAME).xml

SPHINX_PSEUDOXML_FILE = $(SPHINX_OUTPUT_DIR)/pseudoxml/$(PRGNAME).xml

SPHINX_PLAIN_FILE = $(SPHINX_OUTPUT_DIR)/text/$(PRGNAME).txt

SPHINX_PICKLE_FILE = $(SPHINX_OUTPUT_DIR)/pickle/index.fpickle

SPHINX_JSON_FILE = $(SPHINX_OUTPUT_DIR)/json/index.json

SPHINX_HELPHTML_FILE = $(SPHINX_OUTPUT_DIR)/htmlhelp/index.html

SPHINX_QTHELP_FILE = $(SPHINX_OUTPUT_DIR)/qthelp/index.html

SPHINX_DEVHELP_FILE = $(SPHINX_OUTPUT_DIR)/devhelp/index.html

SPHINX_EPUB_FILE = $(SPHINX_OUTPUT_DIR)/epub/$(PRGNAME).epub

endif

################################################################################



############### Compiler settings ##################

# Programming language choose by the user.

# IMPORTANT: Do not comment this variables and remove trailing spaces.
PRG_LANG = C

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_SRC = .c

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_HDR = .h

# Compiler according user choice or automatic to language.
COMPILER = $(CC)

WALL =  -Wall

WEXTRA = -Wextra

# Define the warning the user want.
WARNS = -Wall -Wextra -Wno-missing-field-initializers -Wno-unused-parameter -Wno-deprecated-declarations

# Use the increment operator so that the user can define the flags he want.
CFLAGS = -g -O2 -pedantic

CPPFLAGS =

LDFLAGS = `pkg-config --cflags gtk+-3.0` `xml2-config --cflags` `pkg-config --cflags vte-2.91`
LDLIBS  = `pkg-config --libs gtk+-3.0` `xml2-config --libs` `pkg-config --libs vte-2.91`


# IMPORTANT: Do not comment this variables and remove trailing spaces.
USE_PRG_LIB = F

######## Program informations. #########################

BIN_DIR = ./bin

PRGNAME = mk-project

PRGPATH = $(BIN_DIR)/$(PRGNAME)

VERSION = 2.1

########################################################






SRC_DIR   = ./src

SRC_FILES = $(SRC_DIR)/main.c \
            $(SRC_DIR)/global_vars.c \
            $(SRC_DIR)/cmdline/cmdline.c \
            $(SRC_DIR)/GUI/setup_gui.c \
            $(SRC_DIR)/GUI/gui_callback.c \
            $(SRC_DIR)/GUI/message_dialog.c \
            $(SRC_DIR)/terminals/terminals_callback.c \
            $(SRC_DIR)/terminals/terminals.c \
            $(SRC_DIR)/project/project.c \
            $(SRC_DIR)/project/reconf_project.c \
            $(SRC_DIR)/structures_initialize.c \
            $(SRC_DIR)/project/new_project.c \
            $(SRC_DIR)/project/fmt_files.c \
            $(SRC_DIR)/project/project_functions.c \
            $(SRC_DIR)/project/load_project.c \
            $(SRC_DIR)/make/make_utils.c \
            $(SRC_DIR)/make/make_menu.c \
            $(SRC_DIR)/make/make_actions.c \
            $(SRC_DIR)/xml_utils/xml_getter.c \
            $(SRC_DIR)/xml_utils/xml_utils.c \
            $(SRC_DIR)/xml_utils/xml_writer.c \
            $(SRC_DIR)/configuration/configuration_dialog.c \
            $(SRC_DIR)/configuration/configuration_storing.c \
            $(SRC_DIR)/terminals/GtkMkTerm.c \
            $(SRC_DIR)/GUI/GtkSmartMenuItem.c \
            $(SRC_DIR)/terminals/GtkMkTermTab.c \
            $(SRC_DIR)/GUI/GtkSmartIconButton.c


HDR_DIR = ./headers \
          ./headers/structures

OBJECTS = $(SRC_FILES:.c=.o)


S_FILES  = $(SRC_FILES:$(EXT_SRC)=.s)

CPP_FILES = $(SRC_FILES:$(EXT_SRC)=.i)

#######################################################

#NOTE: not GNU make tools have less capabilities than the original tool.
ifneq ($(notdir $(MAKE)),make)
$(warning You don't use the GNU make tool: this can go into incompatibilities with this Makefile)
endif

# The default or all target is the default target (when you only enter $ make) or the first target encounter in the Makefile.
all: build

build: $(PRGPATH)


#################### [START] Program library target [START] #####################

ifeq ($(USE_PRG_LIB),T)

LIB_NAME = lib$(PRGNAME)

LIB_SRC_PATH = $(SRC_DIR)/$(LIB_NAME)

LIB_PATH = $(LIB_SRC_PATH)/$(LIB_NAME)

$(LIB_NAME):
	cd $(LIB_SRC_PATH) ; $(MAKE)

$(LIB_PATH):
	cd $(LIB_SRC_PATH) ; $(MAKE)

else

LIB_PATH =

endif

################################################################################


# First target appearing is the implicit variable: .DEFAULT: target.
$(PRGPATH):  $(BIN_DIR) $(LIB_PATH) $(OBJECTS)
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)  $(DEBUG_OPTION)  $(PG_OPTION) -o $(PRGPATH) $(OBJECTS) $(LIB_PATH) $(LDLIBS)


.PHONY: $(BIN_DIR)
$(BIN_DIR):
	- @if `test ! -d $(BIN_DIR)` ; then  $(MKDIR_P) $(BIN_DIR) ; fi


%.o: %$(EXT_SRC)
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)  $(DEBUG_OPTION)  $(PG_OPTION)  -c $< -o $@ $(LDLIBS)


assembly: $(S_FILES)

%.s : %$(EXT_SRC)
	$(COMPILER) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -S $(AS_OPTS) $< -o $@ $(LDLIBS)

.PHONY: assembly-att assembly-intel

assembly-att:
	$(MAKE) -B assembly AS_OPTS=-masm=att


assembly-intel:
	$(MAKE) -B assembly AS_OPTS=-masm=intel

assembly-power:
	$(MAKE) -B assembly AS_OPTS=-masm=power

.PHONY: preproc

preproc: $(CPP_FILES)

%.i: %$(EXT_SRC)
	$(COMPILER) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -E $< -o $@ $(LDLIBS)


################################################################################

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
	@echo "$$ export LANGUAGE=fr:en      # Language on French with English callback."
	@echo "$$ export set LANGUAGE=fr:en  # Language on French with English callback."
	@echo "$$ declare LANGUAGE=fr:en     # Language on French with English callback."
else
	@echo  "You must define the lang variable on the command line."
	@echo  "Per example \"make msgfmt lang=fr\" for French."
endif

endif


ifneq ($(MSGUNIQ), )
.PHONY: msguniq
MSGUNIQ_OPTS=
msguniq:
	if `test -f $(PRGNAME).pot` ; then $(MSGUNIQ) $(MSGUNIQ_OPTS) $(PRGNAME).pot -o $(PRGNAME).pot ; fi
endif

################################################################################

#################### [START] Debugging targets [START] #########################

.PHONY: fdebug ddebug gdebug

# File debug.
fdebug:
	- $(RM) -f ./debug.txt
	$(MAKE) $(PRGPATH) 2> ./debug.txt

# Define -DDEBUG
ddebug:
	$(MAKE) -B DEBUG_FLAG=-DDEBUG

# Compile with -g debugging option
gdebug:
	$(MAKE) -B $(PRGPATH) DEBUG_OPTION=-g

ifneq ($(GDB), )
.PHONY: gdb
# Launch interactive gdb (gnu debugger).
GDB_OPTS =
gdb:
	cd $(BIN_DIR) ; $(GDB) $(GDB_OPTS) ./$(PRGNAME)
endif

#################### [END] Debugging targets [END] #############################

######################### [START] Oprofile targets [START] #####################

################################################################
# Use "operf" or "ocount" to generate oprofile_data directory. #
#                                                              #
# Take a look at the "ophelp" output which lists               #
# the available performance counter options.                   #
#                                                              #
################################################################

OPROFILE_DATA=$(BIN_DIR)/oprofile_data

ifneq ($(OPERF), )
.PHONY: operf
OPERF_OPTS =
operf:
	cd $(BIN_DIR) ; $(OPERF) $(OPERF_OPTS) ./$(PRGNAME) $(argv)
endif

ifneq ($(OCOUNT), )
.PHONY: ocount
OCOUNT_OPTS =
ocount:
	cd $(BIN_DIR) ; $(OCOUNT) ./$(PRGNAME) $(argv)
endif

ifneq ($(OPREPORT), )
.PHONY: opreport
OPREPORT_OPTS =
opreport:
	$(OPREPORT) $(OPREPORT_OPTS) --session-dir=$(OPROFILE_DATA)
endif

ifneq ($(OPANNOTATE), )
.PHONY: opannotate
OPANNOTATE_OPTS =
opannotate:
	$(OPANNOTATE) $(OPANNOTATE_OPTS) --session-dir=$(OPROFILE_DATA)
endif

ifneq ($(OPGPROF), )
.PHONY: opgprof
OPGPROF_OPTS =
opgprof:
	cd $(BIN_DIR) ; $(OPGPROF) $(OPGPROF_OPTS) ./$(PRGNAME)
endif

.PHONY: clean_oprofile
clean_oprofile:
	$(RM_R) -f $(OPROFILE_DATA)

######################### [END] Oprofile targets [END] #########################

######################### [START] Valgrind targets [START] #####################

################################################################################
# Valgrind is a flexible program for debugging and                             #
# profiling Linux executables.                                                 #
# $(VALGRIND) --leak-check=full ./$(PRGNAME) $(argv)                           #
#                                                                              #
#--tool=<toolname> [default: memcheck]                                         #
#       Run the Valgrind tool called toolname, e.g. memcheck, cachegrind,      #
#       callgrind, helgrind, drd, massif, lackey, none, exp-sgcheck,           #
#       exp-bbv, exp-dhat, etc.                                                #
################################################################################

ifneq ($(VALGRIND), )
.PHONY: valgrind-memcheck valgrind-cachegrind valgrind-callgrind valgrind-helgrind
VALGRIND_OPTS =
valgrind-memcheck:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=memcheck $(VALGRIND_OPTS) ./$(PRGNAME) $(argv)

valgrind-cachegrind:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=cachegrind $(VALGRIND_OPTS) ./$(PRGNAME) $(argv)

valgrind-callgrind:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=callgrind $(VALGRIND_OPTS) ./$(PRGNAME) $(argv)

valgrind-helgrind:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=helgrind $(VALGRIND_OPTS) ./$(PRGNAME) $(argv)
endif

################################################################################
# It lacks: drd, massif, lackey, none, exp-sgcheck, exp-bbv, exp-dhat, etc.    #
#                                                                              #
# If you get interest in this tools modify the template                        #
# adding the targets you want.                                                 #
# Be simply careful about the character "%" which must be escape with: "%".   #
################################################################################


#################### [START] program analyze tools targets [START] #############

# Default -pg option filename.
PG_FILE = $(BIN_DIR)/gmon.out

ifeq ($(MAKECMDGOALS),gprof)
test_gmon = $(call FILE_EXIST, $(PG_FILE))
ifneq ($(test_gmon),T)
$(info  )
$(info ***************************************************************)
$(info You must first execute your program so that it can be profiled,)
$(info it generate the profiling file gmon.out by runtime,)
$(info then you can analyse it content with gprof...)
$(info ***************************************************************)
$(info  )
$(error $(PG_FILE) missing)
endif
endif


.PHONY: pg gprof
pg:
	$(MAKE) -B clean_pg
	$(MAKE) clean
	$(MAKE) PG_OPTION=-pg

ifneq ($(GPROF), )
# You must execute your program to generate the gmon.out file.
# Edit the wanted options to give to gprof program.
GPROF_OPTS =
gprof: $(PG_FILE)
	$(GPROF) $(GPROF_OPTS) $(PRGPATH) $(PG_FILE)
endif

ifneq ($(STRACE), )
# Edit the wanted options to give to strace program.
STRACE_OPTS =
strace: $(PRGPATH)
	$(STRACE) $(STRACE_OPTS) $(PRGPATH)
endif

ifneq ($(LTRACE), )
# Edit the wanted options to give to strace program.
LTRACE_OPTS =
ltrace: $(PRGPATH)
	$(LTRACE) $(STRACE_OPTS) $(PRGPATH)
endif

ifneq ($(NM), )
# Edit the wanted options to give to nm program.
NM_OPTS =
nm: $(PRGPATH)
	$(NM) $(NM_OPTS) $(PRGPATH)
endif

ifneq ($(OBJDUMP), )
# Edit the wanted options to give to objdump program. # One is required from the program.
OBJDUMP_OPTS =
# objdump require an option.
objdump: $(PRGPATH)
	$(OBJDUMP) $(OBJDUMP_OPTS) $(PRGPATH)
endif

ifneq ($(LDD), )
# Edit the wanted options to give to ldd program.
LDD_OPTS =
ldd:$(PRGPATH)
	$(LDD) $(LDD_OPTS) $(PRGPATH)
endif

ifneq ($(HEXDUMP), )
# Edit the wanted options to give to hexdump program.
HEXDUMP_OPTS =
.PHONY: hexdump
hexdump: $(PRGPATH)
	$(HEXDUMP) $(HEXDUMP_OPTS) $(PRGPATH)
endif

ifneq ($(DIFF), )
# Edit the wanted options to give to diff program.
# -q -y  -t --suppress-blank-empty --suppress-common-lines --show-c-function
DIFF_OPTS =
.PHONY: diff
diff:
ifneq ($(argv), )
	$(DIFF) $(DIFF_OPTS) "$(argv)"
else
	@echo "You must provide 2 filepath given on the cmdline:"
	@echo "$ make diff argv=\"filepath1 filepath2\""
endif
endif

#################### [END] program analyze tools targets [END] #################




#################### [START] Code formatters configuration [START] #############

OVERWRITE = F

USE_INDENT = T

USE_ASTYLE = T

USE_BCPP = T

USE_TABS = F

INDENTATION = 2

# Edit your options like you want for target indent-user.
INDENT_OPTS =

# Edit your options like you want for target astyle-user.
ASTYLE_OPTS =

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


#################### [START] Documentation settings [START] ####################

USE_SPHINX=T

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



#################### [START] Distributing targets [START] ######################

COMPRESSION = 3

DIST_DIR  = ./dist

PATH_TO_REALSE_FILE = ./.release/RELEASE.txt

GET_RELEASE_NB = $(shell cat $(PATH_TO_REALSE_FILE))

SET_RELEASE_NB = $(file $1 > $(PATH_TO_REALSE_FILE))


DIST_NAME = $(PRGNAME)-$(VERSION)-$(RELEASE)

DIST_NAME = $(PRGNAME)-$(VERSION)-$$RELEASE

DIST_EXCLUDE_FOLDER = bin dist

TAR_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), --exclude=$(var)/*)

ZIP_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), -x $(var)/\*)

RAR_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), -x=./$(var)/*)



.PHONY: $(DIST_DIR)

$(DIST_DIR):
	@- if `test ! -d $(DIST_DIR)` ; then $(MKDIR_P) $(DIST_DIR) ; fi

ifneq ($(ZIP), )
.ONESHELL:
.PHONY: pkg-zip
pkg-zip: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(ZIP) -r  $(ZIP_EXCLUDE_CMD)  -$(COMPRESSION) -o -v  $(TMP_DIR)/$(DIST_NAME).zip .
	$(ZIP) $(TMP_DIR)/$(DIST_NAME).zip $(DIST_EXCLUDE_FOLDER)
	$(MV) $(TMP_DIR)/$(DIST_NAME).zip $(DIST_DIR)/$(DIST_NAME).zip
	$(ZIP) -T $(DIST_DIR)/$(DIST_NAME).zip
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).zip
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).zip
endif

ifneq ($(TAR), )
.ONESHELL:
.PHONY: pkg-tar
pkg-tar: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar $(DIST_DIR)/$(DIST_NAME).tar
	$(TAR) --test-label -f $(DIST_DIR)/$(DIST_NAME).tar
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar
endif

ifneq ($(TAR), )
ifneq ($(GZ), )
.ONESHELL:
.PHONY: pkg-tar-gz
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --gzip -xf $(TARNAME).tar.gz                           #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-gz: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.gz .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.gz $(DIST_DIR)/$(DIST_NAME).tar.gz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.gz $(TMP_DIR)/$(DIST_NAME).tar.gz
	$(GZ) -v -t $(DIST_DIR)/$(DIST_NAME).tar.gz
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.gz
endif
endif

ifneq ($(TAR), )
ifneq ($(BZ2), )
.ONESHELL:
.PHONY: pkg-tar-bz2
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --bzip2 -xf $(TARNAME).tar.bz2                         #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-bz2: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.bz2 .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.bz2 $(DIST_DIR)/$(DIST_NAME).tar.bz2
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.bz2 $(TMP_DIR)/$(DIST_NAME).tar.bz2
	$(BZ2) -v -t $(DIST_DIR)/$(DIST_NAME).tar.bz2
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.bz2
endif
endif

ifneq ($(TAR), )
ifneq ($(XZ), )
.ONESHELL:
.PHONY: pkg-tar-lzma
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --lzma -xf $(TARNAME).tar.lzma                         #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-lzma: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.lzma .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.lzma $(DIST_DIR)/$(DIST_NAME).tar.lzma
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.lzma
	$(XZ) -v -t $(DIST_DIR)/$(DIST_NAME).tar.lzma
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.lzma
endif
endif

ifneq ($(TAR), )
ifneq ($(LZOP), )
.ONESHELL:
.PHONY: pkg-tar-lzop
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --lzop -xf $(TARNAME).tar.lzo                          #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-lzop: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.lzo .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.lzo $(DIST_DIR)/$(DIST_NAME).tar.lzo
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.lzo
	$(LZOP) -v -t $(DIST_DIR)/$(DIST_NAME).tar.lzo
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.lzo
endif
endif

ifneq ($(TAR), )
ifneq ($(LZIP), )
.ONESHELL:
.PHONY: pkg-tar-lzip
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --lzip -xf $(TARNAME).tar.lz                           #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-lzip: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.lz .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.lz $(DIST_DIR)/$(DIST_NAME).tar.lz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.lz
	$(LZIP) -v -t $(DIST_DIR)/$(DIST_NAME).tar.lz
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.lz
endif
endif

ifneq ($(TAR), )
ifneq ($(XZ), )
.ONESHELL:
.PHONY: pkg-tar-xz
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --xz -xf $(TARNAME).tar.xz                             #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-xz: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.xz .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.xz $(DIST_DIR)/$(DIST_NAME).tar.xz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.xz
	$(XZ) -v -t --format=xz $(DIST_DIR)/$(DIST_NAME).tar.xz
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.xz
endif
endif

ifneq ($(RAR), )
.ONESHELL:
.PHONY: pkg-rar
######################################################################
# -m<n>   Set compression method:                                    #
#                                                                    #
#       -m0   store     do not compress file when adding to archive  #
#       -m1   fastest   use fastest method (less compressive)        #
#       -m2   fast      use fast compression method                  #
#       -m3   normal    use normal (default) compression method      #
#       -m4   good      use good compression method (more            #
#                       compressive, but slower)                     #
#       -m5   best      use best compression method (slightly more   #
#                       compressive, but slowest)                    #
#                                                                    #
#            If this switch is not specified, RAR uses -m3 method    #
#            (normal compression).                                   #
######################################################################
pkg-rar: $(DIST_DIR)
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)-$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_REALSE_FILE)
	$(RAR) a $(TMP_DIR)/$(DIST_NAME).rar va $(RAR_EXCLUDE_CMD) -r -s .
	$(MV) $(TMP_DIR)/$(DIST_NAME).rar $(DIST_DIR)/$(DIST_NAME).rar
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).rar
	$(RAR) t $(DIST_DIR)/$(DIST_NAME).rar
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).rar
endif

#################### [END] Distributing targets [END] ##########################



#################### [START] cleaning targets [START] ##########################

.PHONY: clean_all clean_o clean_lib clean_save clean_prg clean_pg clean clean_doc clean_s clean_cpp

clean_prg:
	- $(RM) -f $(PRGPATH)

ifneq ($(FIND), )
.PHONY: clean_save
clean_save:
	$(FIND) . -iregex .*~$$ -exec rm -f {} \;
endif

clean_pg:
	- $(RM) -f $(PG_FILE)

clean_o:
	- $(RM) -f $(OBJECTS)

clean_lib:
	- $(RM) -f $(LIB_PATH)

clean_cpp:
	- $(RM) -f $(CPP_FILES)

clean_s:
	- $(RM) -f $(S_FILES)

.PHONY: clean_doc
clean_doc:
	- $(RM) -f $(INFO_FILE) $(TEXT_FILE) $(PDF_FILE) $(HTML_FILE) $(HTML5_FILE) $(TEXI_FILE) $(ODT_FILE) $(XML_FILE) $(LATEX_FILE) $(ASCIIDOC_FILE) $(EPUB_FILE)

.PHONY: clean_doc_gen
clean_doc_gen:
	- $(RM) -f $(TEXI_FILE) $(TEXI_MAN_FILE) $(TEXI_INFO_FILE) $(TEXI_PDF_FILE) $(TEXI_HTML_FILE) $(TEXI_HTML5_FILE) $(TEXI_ODT_FILE) $(TEXI_XML_FILE) $(TEXI_LATEX_FILE) $(TEXI_ASCIIDOC_FILE) $(TEXI_EPUB_FILE) $(TEXI_PLAIN_FILE) \
	                        $(RST_MAN_FILE)  $(RST_INFO_FILE)  $(RST_PDF_FILE)  $(RST_HTML_FILE)  $(RST_HTML5_FILE)  $(RST_ODT_FILE)  $(RST_XML_FILE)  $(RST_LATEX_FILE)  $(RST_ASCIIDOC_FILE)  $(RST_EPUB_FILE)  $(RST_PLAIN_FILE) \
	                        $(MD_MAN_FILE)   $(MD_INFO_FILE)   $(MD_PDF_FILE)   $(MD_HTML_FILE)   $(MD_HTML5_FILE)   $(MD_ODT_FILE)   $(MD_XML_FILE)   $(MD_LATEX_FILE)   $(MD_ASCIIDOC_FILE)   $(MD_EPUB_FILE)   $(MD_PLAIN_FILE)



clean_all: clean_o clean_prg clean_save clean_pg clean_s clean_lib clean_cpp

clean: clean_o clean_prg

#################### [END] cleaning targets [END] ##############################


#################### [START] utilities targets [START] #########################

.PHONY: strip info exec

ifneq ($(FIND), )
.PHONY: list-project
list-project:
	$(FIND) * -exec file {} \;
endif



ifneq ($(STRIP), )
strip:
	strip $(PRGPATH)
endif

# Put the informations you need in this target.
info:
	@echo
	@ls -l $(PRGPATH) ; # Must make a personal tool displaying file size in K but with the comma rest.
	@echo
ifneq ($(FILE), )
	@file $(PRGPATH)  ;
	@echo
endif
ifneq ($(SIZE), )
	@size $(PRGPATH)  ;
	@echo
endif
	@ls -s -h $(PRGPATH) ;
	@echo



.PHONY: set_x
set_x:
	@ if `test ! -x $(PRGPATH)` ; then $(CHMOD) u+x $(PRGPATH) ; fi


# Overwrite on the cmdline or set it in Makefile if your program need some args.
# or call make by defining this variable:
# $ make argv="foo bar" exec
#
# ATTENTION: the program is launched from inside the directory ./bin !
#            So you can use the defines.h header for defining constants in
#            relationship to the launching directory:
#            * By development: the definition of the macro PREFIX is not done.
#            * By installation: on the target simply define PREFIX to the wanted
#             location for your binary on the target host by compilation.
################################################################################
exec: $(PRGPATH)
# The execute bit removed can append by sharing executable on different device or file systems.
	@ $(MAKE) set_x
	cd $(BIN_DIR) ; ./$(PRGNAME) $(argv)


ifneq ($(GREP), )
GREP_OPTS =
.PHONY: search-pattern
search-pattern:
	cd src ; $(GREP) $(GREP_OPTS) -r -n --color=auto "$(argv)"
endif

ifneq ($(FIND), )
ifneq ($(SED), )
.PHONY: rm-trailing-spaces
rm-trailing-spaces:
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_SRC) -exec $(SED) -i 's/[[:space:]]$$//' {} \;
	$(FIND) $(HDR_DIR) -iregex .*\$(EXT_HDR) -exec $(SED) -i 's/[[:space:]]$$//' {} \;
endif
endif

.PHONY: prepend-license
prepend-license:
ifneq ($(BOILERPLATE_PATH), )
ifneq ($(PRG_LANG), )
ifneq ($(PYTHON), )
ifneq ($(CHMOD), )
	$(CHMOD) a+rx $(PREPEND_LICENSE_SCRIPT)
	$(PYTHON) $(PREPEND_LICENSE_SCRIPT) -d $(SRC_DIR) -f $(BOILERPLATE_PATH) -l $(PRG_LANG)
	$(PYTHON) $(PREPEND_LICENSE_SCRIPT) -d $(HDR_DIR) -f $(BOILERPLATE_PATH) -l $(PRG_LANG)
endif
endif
endif
endif

ifneq ($(SED), )
.PHONY: replace-in-file
replace-in-file:
ifneq ($(pattern), )
	@if `test -f $(file)` ; \
	then $(SED) --in-place "s/$(pattern)/$(replace)/" $(file) ; \
	else echo "$(file) is not a valid filepath" ; fi
else
	@echo "You must provide a pattern to replace !"
	@echo "$ make replace-in-file pattern=\"\" replace=\"\" file=\"\""
endif
endif

ifneq ($(FIND), )
ifneq ($(SED), )
.PHONY: replace-all
replace-all:
ifneq ($(pattern), )
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_SRC) -exec $(SED) --in-place "s/$(pattern)/$(replace)/" {} \;
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_HDR) -exec $(SED) --in-place "s/$(pattern)/$(replace)/" {} \;
else
	@echo "You must provide a pattern to replace !"
	@echo "$ make replace-all pattern=\"\" replace=\"\""
endif
endif
endif


#################### [END] utilities targets [END] #############################


#### [START] test installation targets [START] ####

.PHONY: desktop install-info install-man install-doc install

desktopdir  = /usr/share/applications

desktop:
	- @echo "[Desktop Entry]" > $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Name=mk-project" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "GenericName=make-project" >> $(DESTDIR)$(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Comment=A tool to ease the development process and a good bridge for the distributing process." >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Exec=mk-project %f" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Icon=$(pkgdatadir)/icons/mk-project_icon.png" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Terminal=false" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "X-MultipleArgs=false" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "StartupNotify=true" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Type=Application" >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "MimeType=application/x-extension-mkp;"  >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Keywords=Development;Programming;Terminal;TDE;make;"  >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	- @echo "Categories=Development;IDE;GTK;"  >> $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop
	echo "desktop file generated at: $(DESTDIR)$(desktopdir)/$(PRGNAME).desktop"

update-desktop:
	- xdg-desktop-menu  install --mode system "$(DESTDIR)$(desktopdir)/$(PRGNAME).desktop"
	- xdg-icon-resource install --context mimetypes --size 16 "$(DESTDIR)$(pkgdatadir)/icons/set/16x16/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 22 "$(DESTDIR)$(pkgdatadir)/icons/set/22x22/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 24 "$(DESTDIR)$(pkgdatadir)/icons/set/24x24/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 32 "$(DESTDIR)$(pkgdatadir)/icons/set/32x32/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 36 "$(DESTDIR)$(pkgdatadir)/icons/set/36x36/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 42 "$(DESTDIR)$(pkgdatadir)/icons/set/42x42/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 48 "$(DESTDIR)$(pkgdatadir)/icons/set/48x48/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 64 "$(DESTDIR)$(pkgdatadir)/icons/set/64x64/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 72 "$(DESTDIR)$(pkgdatadir)/icons/set/72x72/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 96 "$(DESTDIR)$(pkgdatadir)/icons/set/96x96/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 128 "$(DESTDIR)$(pkgdatadir)/icons/set/128x128/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 192 "$(DESTDIR)$(pkgdatadir)/icons/set/192x192/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 256 "$(DESTDIR)$(pkgdatadir)/icons/set/256x256/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context mimetypes --size 512 "$(DESTDIR)$(pkgdatadir)/icons/set/512x512/mk-project_icon.png" "application-x-extension-mkp"
	- xdg-icon-resource install --context apps --size 16 "$(DESTDIR)$(pkgdatadir)/icons/set/16x16/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 22 "$(DESTDIR)$(pkgdatadir)/icons/set/22x22/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 24 "$(DESTDIR)$(pkgdatadir)/icons/set/24x24/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 32 "$(DESTDIR)$(pkgdatadir)/icons/set/32x32/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 36 "$(DESTDIR)$(pkgdatadir)/icons/set/36x36/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 42 "$(DESTDIR)$(pkgdatadir)/icons/set/42x42/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 48 "$(DESTDIR)$(pkgdatadir)/icons/set/48x48/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 64 "$(DESTDIR)$(pkgdatadir)/icons/set/64x64/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 72 "$(DESTDIR)$(pkgdatadir)/icons/set/72x72/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 96 "$(DESTDIR)$(pkgdatadir)/icons/set/96x96/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 128 "$(DESTDIR)$(pkgdatadir)/icons/set/128x128/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 192 "$(DESTDIR)$(pkgdatadir)/icons/set/192x192/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 256 "$(DESTDIR)$(pkgdatadir)/icons/set/256x256/mk-project_icon.png" "mk-project"
	- xdg-icon-resource install --context apps --size 512 "$(DESTDIR)$(pkgdatadir)/icons/set/512x512/mk-project_icon.png" "mk-project"
	- xdg-icon-resource forceupdate --mode system
	- xdg-desktop-menu forceupdate --mode system
 
unupdate-desktop:
	- xdg-icon-resource uninstall --context apps --size 16 "$(DESTDIR)$(pkgdatadir)/icons/set/16x16/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 22 "$(DESTDIR)$(pkgdatadir)/icons/set/22x22/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 24 "$(DESTDIR)$(pkgdatadir)/icons/set/24x24/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 32 "$(DESTDIR)$(pkgdatadir)/icons/set/32x32/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 36 "$(DESTDIR)$(pkgdatadir)/icons/set/36x36/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 48 "$(DESTDIR)$(pkgdatadir)/icons/set/48x48/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 64 "$(DESTDIR)$(pkgdatadir)/icons/set/64x64/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 72 "$(DESTDIR)$(pkgdatadir)/icons/set/72x72/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 96 "$(DESTDIR)$(pkgdatadir)/icons/set/96x96/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 128 "$(DESTDIR)$(pkgdatadir)/icons/set/128x128/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 192 "$(DESTDIR)$(pkgdatadir)/icons/set/192x192/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 256 "$(DESTDIR)$(pkgdatadir)/icons/set/256x256/mk-project_icon.png" "mk-project"
	- xdg-icon-resource uninstall --context apps --size 512 "$(DESTDIR)$(pkgdatadir)/icons/set/512x512/mk-project_icon.png" "mk-project"
	- xdg-icon-resource forceupdate --mode system
	- xdg-desktop-menu forceupdate --mode system

install-info:
	- if `test ! -d "$(DESTDIR)$(infodir)"` ; then $(MKDIR_P) "$(DESTDIR)$(infodir)" ; fi
	- $(INSTALL) ./texi/mk-project.info "$(DESTDIR)$(infodir)"

install-man:
	- if `test ! -d "$(DESTDIR)$(man1dir)"` ; then $(MKDIR_P) "$(DESTDIR)$(man1dir)" ; fi
	- $(INSTALL) ./man/mk-project.1 "$(DESTDIR)$(man1dir)"

install-doc:
	- if `test ! -d $(DESTDIR)$(docdir)` ; then $(MKDIR_P) "$(DESTDIR)$(docdir)" ; fi
	- $(INSTALL) ./doc/mk-project.html "$(DESTDIR)$(docdir)"
	- $(INSTALL) ./doc/mk-project.pdf  "$(DESTDIR)$(docdir)"



install:
# If you don't define PREFIX you can modify compile and test the program here.
	- $(MAKE) -B CPPFLAGS=-D'PREFIX=\"$(DESTDIR)$(prefix)\"'
	- $(INSTALL) $(PRGPATH) "$(DESTDIR)$(bindir)"
#	- $(CP_R) "$(srcdir)/share/$(PRGNAME)/" "$(DESTDIR)$(pkgdatadir)"
	- $(CP_R) ./share/* $(DESTDIR)$(prefix)/share/
	- $(CHMOD) -R a+rx "$(DESTDIR)$(pkgdatadir)"
	- $(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/configuration"
	- $(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/bin"
	- if `test ! -d "$(DESTDIR)$(pkgdatadir)/src"` ; then $(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/src" ; fi
	- $(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/src"
	- $(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/bin"
	- $(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/icons/set/"
	- $(MAKE) desktop
	- $(MAKE) update-desktop
	- $(MAKE) install-info
	- $(MAKE) install-man
	- $(MAKE) install-doc
	- $(MAKE) clean

uninstall:
	- $(MAKE) unupdate-desktop
	- $(RM) -f "$(DESTDIR)$(bindir)/$(PRGNAME)"
	- $(RM) -f "$(DESTDIR)$(infodir)/$(PRGNAME).info"
	- $(RM) -f "$(DESTDIR)$(man1dir)/$(PRGNAME).1"
	- $(RM) -f "$(DESTDIR)$(docdir)/$(PRGNAME).html"
	- $(RM) -f "$(DESTDIR)$(docdir)/$(PRGNAME).pdf"
	- $(RM) -f "$(desktopdir)/$(PRGNAME).desktop"
	- $(RM_R) -f $(pkgdatadir)

###### [END] test installation target [END] #######




#################### [START] print available targets [START] ###################

.PHONY: help

help:
	@echo "make build      # Build the binary."
	@echo "make exec       # Execute the binary."
	@echo
	@echo "make ddebug     # Build the binary with DEBUG flag defined."
	@echo "make gdebug     # Build the binary with the debugging -g option."
	@echo "make gdb        # Launch gdb with the binary given as argument."
	@echo "make fdebug     # Build the binary and generate a debug.txt file from the build."
	@echo "make pg         # Build the binary with the profiling -pg option."
	@echo "make gprof      # Launch the gprof tool."
	@echo
	@echo "make assembly-att    # Generate assembly files (AT&T syntax) from src files."
	@echo "make assembly-intel  # Generate assembly files (Intel syntax) from src files."
	@echo "make assembly-power  # Generate assembly files (Power syntax) from src files."
	@echo
	@echo "make preproc    # Generate preprocessor file (*.i) from source files."
	@echo
ifneq ($(HEXDUMP), )
	@echo "make hexdump    # Process a hexdump on the program."
	@echo
endif
	@echo "make info       # Print binary file informations."
	@echo
ifneq ($(STRIP), )
	@echo "make strip      # strip the binary."
	@echo
endif
	@echo "make clean           # Remove all object files and the binary."
	@echo "make clean_o         # Remove all object files."
	@echo "make clean_prg       # Remove the binary file."
	@echo "make clean_lib       # Remove the static library (ar) file if any."
	@echo "make clean_s         # Remove all assembly generated files."
	@echo "make clean_cpp       # Remove all preprocessor files."
	@echo "make clean_pg        # Remove gmon.out file."
	@echo "make clean_all       # Remove all generated files."
	@echo "make clean_doc       # Remove all documentation files."
	@echo "make clean_oprofile  # Remove the oprofile session directory."
	@echo
ifneq ($(FIND), )
	@echo "make clean_save # Remove backup files."
	@echo
endif
ifneq ($(OPERF), )
	@echo "make operf      # This is the program for collecting profile data."
endif
ifneq ($(OCOUNT), )
	@echo "make ocount     # This tool is used for simple event counting."
endif
ifneq ($(OPREPORT), )
	@echo "make opreport   # This is the main tool for retrieving useful profile data."
endif
ifneq ($(OPANNOTATE), )
	@echo "make opannotate # This utility can be used to produce annotated source."
endif
ifneq ($(OPGPROF), )
	@echo "make opgprof    # This utility can output gprof-style data files for a binary."
	@echo
endif
ifneq ($(VALGRIND), )
	@echo "make valgrind-memcheck   # Launch the valgrind memcheck tool on your binary."
	@echo "make valgrind-cachegrind # Launch the valgrind cachegrind tool on your binary."
	@echo "make valgrind-callgrind  # Launch the valgrind callgrind tool on your binary."
	@echo "make valgrind-helgrind   # Launch the valgrind helgrind tool on your binary."
	@echo
endif
ifneq ($(GREP), )
	@echo "make search-pattern argv=pattern # Search for pattern in files."
	@echo
endif
ifneq ($(SED), )
	@echo "make replace-in-file pattern=\"\" replace=\"\" file=\"\" # Replace pattern in file."
	@echo
endif
ifneq ($(FIND), )
ifneq ($(SED), )
	@echo "make replace-all pattern=\"\" replace=\"\" # Replace pattern in all src files."
	@echo
endif
endif
ifneq ($(FIND), )
ifneq ($(SED), )
	@echo "make rm-trailing-spaces # Remove trailing spaces from source and headers."
	@echo
endif
endif
	@echo "make prepend-license    # Prepends license to all source and headers files."
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
ifneq ($(STRACE), )
	@echo "make strace      # trace the binary."
endif
ifneq ($(LTRACE), )
	@echo "make ltrace      # ltrace the binary."
endif
ifneq ($(NM), )
	@echo "make nm          # process the binary the nm tool."
endif
ifneq ($(OBJDUMP), )
	@echo "make objdump     # Process the binary the objdump tool."
endif
ifneq ($(LDD), )
	@echo "make ldd         # Process the binary with the ldd tool."
endif
	@echo
ifeq ($(USE_INDENT),T)
ifneq ($(INDENT), )
	@echo "make indent-kr    # Format all source files in the kr style."
	@echo "make indent-gnu   # Format all source files in the gnu style."
	@echo "make indent-linux # Format all source files in the linux style."
	@echo "make indent-orig  # Format all source files in the original style."
	@echo "make indent-user  # Format all source files in the user defined style."
	@echo
	@echo "make indent-clean # Remove all formatted files with suffix."
	@echo
endif
endif # USE_INDENT
ifeq ($(USE_ASTYLE),T)
ifneq ($(ASTYLE), )
	@echo "make astyle-ansi          # Format all source files in the ansi style."
	@echo "make astyle-java          # Format all source files in the java style."
	@echo "make astyle-kr            # Format all source files in the kr style."
	@echo "make astyle-stroustrup    # Format all source files in the stroustrup style."
	@echo "make astyle-whitesmith    # Format all source files in the whitesmith style."
	@echo "make astyle-banner        # Format all source files in the banner style."
	@echo "make astyle-gnu           # Format all source files in the gnu style."
	@echo "make astyle-linux         # Format all source files in the linux style."
	@echo "make astyle-horstmann     # Format all source files in the horstmann style."
	@echo "make astyle-lisp          # Format all source files in the lisp style."
	@echo "make astyle-pico          # Format all source files in the pico style."
	@echo "make astyle-python        # Format all source files in the python style."
	@echo "make astyle-user          # Format all source files in the user defined style."
	@echo
	@echo "make astyle-clean         # Remove all formatted files with suffix."
	@echo
endif
endif # USE_ASTYLE
ifeq ($(USE_BCPP),T)
ifneq ($(BCPP), )
	@echo "make bcpp-kr      # Format all source files in the bcpp-kr style."
	@echo "make bcpp-pascal  # Format all source files in the bcpp-pascal style."
	@echo
	@echo "make bcpp-clean   # Remove all formatted files with suffix."
	@echo
endif
endif # USE_BCPP
ifneq ($(TAR), )
	@echo "make pkg-tar      # Generate a tar archive from the project."
ifneq ($(LZMA), )
	@echo "make pkg-tar-lzma # Generate a tar.lzma archive from the project."
endif
ifneq ($(LZIP), )
	@echo "make pkg-tar-lzip # Generate a tar.lz archive from the project."
endif
ifneq ($(LZOP), )
	@echo "make pkg-tar-lzop # Generate a tar.lzo archive from the project."
endif
ifneq ($(XZ), )
	@echo "make pkg-tar-xz   # Generate a tar.xz archive from the project."
endif
ifneq ($(GZ), )
	@echo "make pkg-tar-gz   # Generate a tar.gz archive from the project."
endif
ifneq ($(BZ2), )
	@echo "make pkg-tar-bz2  # Generate a tar.bz2 archive from the project."
endif
endif
ifneq ($(RAR), )
	@echo "make pkg-rar      # Generate a rar archive from the project."
endif
ifneq ($(ZIP), )
	@echo "make pkg-zip      # Generate a zip archive from the project."
	@echo
endif # ZIP ENDIF
ifeq ($(USE_SPHINX),T)
	@echo "make sphinx-show-texi"
	@echo "make sphinx-show-man"
	@echo "make sphinx-show-info"
	@echo "make sphinx-show-pdf"
	@echo "make sphinx-show-latexpdf"
	@echo "make sphinx-show-latexpdfja"
	@echo "make sphinx-show-html"
	@echo "make sphinx-show-dirhtml"
	@echo "make sphinx-show-texinfo"
	@echo "make sphinx-show-xml"
	@echo "make sphinx-show-pseudoxml"
	@echo "make sphinx-show-plain"
	@echo "make sphinx-show-pickle"
	@echo "make sphinx-show-json"
	@echo "make sphinx-show-helphtml"
	@echo "make sphinx-show-qthelp"
	@echo "make sphinx-show-devhelp"
	@echo "make sphinx-show-epub"
endif # SHOW SPHINX ENDIF

#################### [END] print available targets [END] #######################
