# No license prefixing, you are free to use the license you want.

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
# $%  Target member name if the target is an archive member.
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
MAKE_OPTS = %s

MAKEFLAGS += $(MAKE_OPTS)

SHELL = %s

################################################################################

include ./.SubMakefiles/binary_checks.mk

include ./.SubMakefiles/path.mk

############### Compiler settings ##################

# Programming language choose by the user.

# IMPORTANT: Do not comment this variables and remove trailing spaces.
PRG_LANG = %s

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_SRC = %s

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_HDR = %s

# Compiler according user choice or automatic to language.
COMPILER = %s

WALL =  -Wall

WEXTRA = -Wextra

# Define the warning the user want.
WARNS = %s

# Use the increment operator so that the user can define the flags he want.
CFLAGS = %s

CPPFLAGS = %s

LDFLAGS = %s
LDLIBS  = %s

# IMPORTANT: Do not comment this variables and remove trailing spaces.
USE_PRG_LIB = %s

######## Program informations. #########################

BIN_DIR = ./bin

PRGNAME = %s

PRGPATH = $(BIN_DIR)/$(PRGNAME)

VERSION = %s

########################################################

SRC_DIR   = ./src

SRC_FILES = $(SRC_DIR)/main%s \
            $(SRC_DIR)/global_vars%s



OBJECTS = $(SRC_FILES:$(EXT_SRC)=.o)


S_FILES  = $(SRC_FILES:$(EXT_SRC)=.s)

CPP_FILES = $(SRC_FILES:$(EXT_SRC)=.i)

HDR_DIR   = $(SRC_DIR)/headers

HDR_FILES = $(HDR_DIR)/includes%s \
            $(HDR_DIR)/defines%s  \
            $(SRC_DIR)/global_vars%s

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


%%.o: %%$(EXT_SRC)
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)  $(DEBUG_OPTION)  $(PG_OPTION)  -c $< -o $@ $(LDLIBS)


assembly: $(S_FILES)

%%.s : %%$(EXT_SRC)
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

%%.i: %%$(EXT_SRC)
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
GDB_OPTS = %s
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
OPERF_OPTS = %s
operf:
	cd $(BIN_DIR) ; $(OPERF) $(OPERF_OPTS) ./$(PRGNAME) $(argv)
endif

ifneq ($(OCOUNT), )
.PHONY: ocount
OCOUNT_OPTS = %s
ocount:
	cd $(BIN_DIR) ; $(OCOUNT) ./$(PRGNAME) $(argv)
endif

ifneq ($(OPREPORT), )
.PHONY: opreport
OPREPORT_OPTS = %s
opreport:
	$(OPREPORT) $(OPREPORT_OPTS) --session-dir=$(OPROFILE_DATA)
endif

ifneq ($(OPANNOTATE), )
.PHONY: opannotate
OPANNOTATE_OPTS = %s
opannotate:
	$(OPANNOTATE) $(OPANNOTATE_OPTS) --session-dir=$(OPROFILE_DATA)
endif

ifneq ($(OPGPROF), )
.PHONY: opgprof
OPGPROF_OPTS = %s
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

VALGRIND_MEMCHECK_OPTS = %s
valgrind-memcheck:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=memcheck $(VALGRIND_MEMCHECK_OPTS) ./$(PRGNAME) $(argv)

VALGRIND_CACHEGRIND_OPTS = %s
valgrind-cachegrind:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=cachegrind $(VALGRIND_CACHEGRIND_OPTS) ./$(PRGNAME) $(argv)

VALGRIND_CALLGRIND_OPTS = %s
valgrind-callgrind:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=callgrind $(VALGRIND_CALLGRIND_OPTS) ./$(PRGNAME) $(argv)

VALGRIND_HELGRIND_OPTS = %s
valgrind-helgrind:
	cd $(BIN_DIR) ; $(VALGRIND) --tool=helgrind $(VALGRIND_HELGRIND_OPTS) ./$(PRGNAME) $(argv)
endif

################################################################################
# It lacks: drd, massif, lackey, none, exp-sgcheck, exp-bbv, exp-dhat, etc.    #
#                                                                              #
# If you get interest in this tools modify the template                        #
# adding the targets you want.                                                 #
# Be simply careful about the character "%" which must be escape with: "%%".   #
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
GPROF_OPTS = %s
gprof: $(PG_FILE)
	$(GPROF) $(GPROF_OPTS) $(PRGPATH) $(PG_FILE)
endif

ifneq ($(STRACE), )
# Edit the wanted options to give to strace program.
STRACE_OPTS = %s
strace: $(PRGPATH)
	$(STRACE) $(STRACE_OPTS) $(PRGPATH)
endif

ifneq ($(LTRACE), )
# Edit the wanted options to give to strace program.
LTRACE_OPTS = %s
ltrace: $(PRGPATH)
	$(LTRACE) $(STRACE_OPTS) $(PRGPATH)
endif

ifneq ($(NM), )
# Edit the wanted options to give to nm program.
NM_OPTS = %s
nm: $(PRGPATH)
	$(NM) $(NM_OPTS) $(PRGPATH)
endif

ifneq ($(OBJDUMP), )
# Edit the wanted options to give to objdump program. # One is required from the program.
OBJDUMP_OPTS = %s
# objdump require an option.
objdump: $(PRGPATH)
	$(OBJDUMP) $(OBJDUMP_OPTS) $(PRGPATH)
endif

ifneq ($(LDD), )
# Edit the wanted options to give to ldd program.
LDD_OPTS = %s
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

include ./.SubMakefiles/code_formatter.mk

include ./.SubMakefiles/documentation.mk

include ./.SubMakefiles/distributing.mk

ifeq ($(USE_SPHINX),T)
include ./.SubMakefiles/sphinx.mk
include ./.SubMakefiles/sphinx-show.mk
endif

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

ifneq ($(RST2MAN), )
.PHONY: rst2man view-man
rst2man:
	cd rst2man ; $(RST2MAN) $(PRGNAME).rst > $(PRGNAME).1
view-man:
	cd rst2man ; $(MAN) -l $(PRGNAME).1
endif



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
	$(GREP) $(GREP_OPTS) -r -n --color=auto "$(argv)"
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


#################### Test (un)install: to customize (experimental). ############

MD5SUM = $(call BINARY_EXIST, md5sum)
SHA1SUM = $(call BINARY_EXIST, sha1sum)
SHA256SUM = $(call BINARY_EXIST, sha256sum)
SHA512SUM = $(call BINARY_EXIST, sha512sum)

.PHONY: hash-build
hash-build:
ifneq ($(MD5SUM), )
	echo `$(MD5SUM) $(PRGPATH)` > $(pkgdatadir)/$(PRGNAME).md5
endif
ifneq ($(SHA1SUM), )
	echo `$(SHA1SUM) $(PRGPATH)` > $(pkgdatadir)/$(PRGNAME).sha1
endif
ifneq ($(SHA256SUM), )
	echo `$(SHA256SUM) $(PRGPATH)` > $(pkgdatadir)/$(PRGNAME).sha256
endif
ifneq ($(SHA512SUM), )
	echo `$(SHA512SUM) $(PRGPATH)` > $(pkgdatadir)/$(PRGNAME).sha512
endif


.PHONY: desktop test-install test-uninstall

DESKTOP_DIR = $(prefix)/share/applications

# it were good to use a tool like xdg-desktop-icon or desktop-file-install for installing the *.desktop file.
desktop:
# To edit:
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
# Recompile all with definition of prefix
	- $(MAKE) -B CPPFLAGS="-D'PREFIX=\"$(prefix)\"'"
# Make directory if not available:
	- if `test ! -d "$(DESTDIR)$(prefix)/share/$(PRGNAME)"` ; then $(MKDIR_P) "$(DESTDIR)$(prefix)/share/$(PRGNAME)" ; fi
# Copy all files contains into ./share/$(PRGNAME) to ${pkgdatadir} directory.
	- $(CP_R) "./share/*" "$(DESTDIR)$(prefix)/share/"
# For special requirement like this:
#	$(CHMOD) -R a+rx $(DESTDIR)$(prefix)/share/$(PRGNAME)
#	$(CHMOD) -R a+rwx $(DESTDIR)$(prefix)/share/$(PRGNAME)/configuration
	$(INSTALL_PROGRAM) "./bin/$(PRGNAME)" "$(DESTDIR)$(bindir)/$(PRGNAME)"
	$(MAKE) hash-build
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




#################### [START] print available targets [START] ###################

.PHONY: help

help:
	@echo "make build      # Build the binary."
	@echo "make exec       # Execute the binary."
%s
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
ifneq ($(RST2MAN), )
	@echo "make rst2man"  # Build a man-page from ReST.
	@echo
	@echo "make view-man" # Display builded man page.
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
