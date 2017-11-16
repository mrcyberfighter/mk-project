# No license prefixing, you are free to use the license you want.

#################### [Start] functions [Start] #################################

# Define a function to check the presence of an executable through his binary path.
BINARY_CHECK = $(shell which $1 2> /dev/null)

BINARY_EXIST = $(if $(call BINARY_CHECK, $1 ), $(call BINARY_CHECK, $1 ))

# Define a function to check if a file exists.
FILE_EXIST   = $(if `test -f $1`,T,F)

# Define a function to check if a directory exists.
DIR_EXIST = $(if `test -d $1`,T,F)

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

# gdb: the GNU debugger.
# you can debug your code with this tool.
GDB = $(call BINARY_EXIST, gdb)

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
