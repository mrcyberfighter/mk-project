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
# define var =   value  # indirect.
# define var :=  value  # direct.
# define var ::= value  #
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


#################### [Start] functions [Start] #################################

# Define a function to check the presence of an executable through his binary path.
BINARY_CHECK = $(shell which $1)

BINARY_EXIST = $(if $(call BINARY_CHECK, $1 ), $(call BINARY_CHECK, $1 ))

# Define a function to check if a file exist.
FILE_EXIST   = $(shell if `test -f $1` ; then echo T ; else echo F ; fi)

################################################################################


############### [START] Check GNU make tool purpose [START] ####################

# NOTE: Use the defined $(MAKE) variable for calling the make tool in recipes.

MAKE    = $(call BINARY_EXIST, make)

############### [END] Check GNU make tool purpose [END] ########################

############### [START] Check coreutils tools [START] ##########################

MKDIR   = $(call BINARY_EXIST, mkdir)

MKDIR_P = $(MKDIR) -p

BASENAME = $(call BINARY_EXIST, basename)

CP = $(call BINARY_EXIST, cp)

CP_R = $(CP) -R

RM = $(call BINARY_EXIST, rm)

RM_R = $(RM) -R

MV  =  $(call BINARY_EXIST, mv)

CHMOD = $(call BINARY_EXIST, chmod)

TOUCH = $(call BINARY_EXIST, touch)

############### [END] Check coreutils tools [END] ##############################


########## [START] installation variables [START] ##############################

INSTALL  = $(call BINARY_EXIST, install)

INSTALL = $(INSTALL) -c

INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA    = ${INSTALL} -m 644
INSTALL_DATA_RW = ${INSTALL} -m 666

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

GREP  = $(call BINARY_EXIST, grep)

# Package ???
HEXDUMP = $(call BINARY_EXIST, hexdump)

# Install the install-info package if missing.
INSTALL_INFO = $(call BINARY_EXIST, install-info)

#################### [End] Other needed binaries [End] #########################





############### Compiler settings ##################

# Programming language choosen by the user.

# IMPORTANT: Do not comment this variables and remove trailing spaces.
PRG_LANG = %s

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_SRC = %s

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_HDR = %s

# Compiler according user choice or automatique to language.
COMPILER = %s

WALL =  -Wall

WEXTRA = -Wextra

WARNS = %s

# Use the increment operator so that the user can define the flags he want.
CFLAGS     += %s

CPPFLAGS   = %s

LDFLAGS = %s
LDLIBS  = %s


######## library informations. #########################


########################################################

LIB_NAME  = %s

SRC_DIR   = ./$(LIB_NAME)

# Collecting source files.
SRC_FILES = $(wildcard *$(EXT_SRC))

OBJECTS = $(SRC_FILES:$(EXT_SRC)=.o)

S_FILES  = $(SRC_FILES:$(EXT_SRC)=.s)

HDR_DIR   =

HDR_FILES =


override AR_OPTS := rcs

all: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	$(AR) $(AR_OPTS) $(LIB_NAME) $(OBJECTS)
	ranlib $(LIB_NAME)

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

################################################################################

#################### [START] Debugging targets [START] #########################

# .PHONY: targets are run everytime you call it with:
# $ make phony_target
.PHONY: fdebug ddebug gdebug gdb

# File debug.
fdebug:
	- $(RM) -f ./debug.txt
	$(MAKE) $(LIB_NAME) 2> ./debug.txt

# Define -DDEBUG
ddebug:
	$(MAKE) -B DEBUG_FLAG=-DDEBUG

# Compile with -g debugging option
gdebug:
	$(MAKE) -B $(LIB_NAME) DEBUG_OPTION=-g

#################### [END] Debugging targets [END] #############################


#### [START] cleaning targets [START] ####

.PHONY: clean_all clean_o clean_save clean_lib clean_pg clean  clean_s

clean_lib:
	- $(RM) -f $(LIB_NAME)

ifneq ($(FIND), )
.PHONY: clean_save
clean_save:
	$(FIND) . -iregex .*~$$ -exec rm -f {} \;
endif

clean_o:
	- $(RM) -f $(OBJECTS)

clean_s:
	- $(RM) -f $(S_FILES)

clean_all: clean_o clean_lib clean_save clean_pg clean_s

clean: clean_o clean_lib

#### [END] cleaning targets [END] ####