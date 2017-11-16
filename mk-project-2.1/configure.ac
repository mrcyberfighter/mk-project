#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Copyright (c)  2016,2017  Brüggemann Eddie.
# Permission is granted to copy, distribute and/or modify this document
# under the terms of the GNU Free Documentation License, Version 1.3
# or any later version published by the Free Software Foundation;
# with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
# A copy of the license is included in the section entitled "GNU
# Free Documentation License".

AC_PREREQ([2.69])
AC_INIT([mk-project], [2.1], [mrcyberfighter@gmail.com], [], [http://www.open-source-projects.net/mk-project/mk-project])

AC_CONFIG_SRCDIR([./src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])



AC_LANG([C])

# Checks for programs.
AC_COPYRIGHT([GPLv3])




AC_CANONICAL_BUILD
AC_CANONICAL_HOST


case $host_os in

  *linux-gnu*)
 
    platform_win32=no
    native_win32=no
    platform_linux=yes
    platform_darwin=no
   
    # It works well on linux system.
   
    ;;

  pw32* | *cygwin*)
 
    platform_win32=yes
    native_win32=no
    platform_linux=no
    platform_darwin=no
   
    # I get trouble to compile the program because
    # libvte-2.91-dev was installed but it does not appear
    # into the `pkg-config --list-all` command ???
   
    ;;


  *darwin*)
 
    platform_win32=no
    native_win32=no
    platform_darwin=yes
    platform_linux=no
 
    # The program compile with success but does not work as expected.
   
    ;;

esac

AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")
AM_CONDITIONAL(PLATFORM_LINUX, test x"$platform_linux" = "xyes")
AM_CONDITIONAL(PLATFORM_DARWIN, test x"$platform_darwin" = "xyes")


# COMPILER M4.
# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O    # ac_cv_prog_cc_compiler_c_o
AC_PROG_CPP
AC_PROG_CC_STDC
AC_PROG_CC_C99    # ac_cv_prog_cc_c99
AC_C_INLINE
AC_C_CONST

# POSIX programs detection.
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_LN_S
AC_PROG_MAKE_SET
#AC_PROG_SED

############### Checking for packages ############

############### Required packages ################

# coreutils package
AC_PATH_PROG([CHMOD],       [chmod],      [no])
AC_PATH_PROG([RM],          [rm],         [no])
AC_PATH_PROG([MV],          [mv],         [no])
AC_PATH_PROG([CP],          [cp],         [no])
AC_PATH_PROG([UNLINK],      [unlink],     [no])
AC_PATH_PROG([RMDIR],       [rmdir],      [no])
AC_PATH_PROG([TOUCH],       [touch],      [no])

AC_PATH_PROG([MD5SUM],      [md5sum],      [no])
AC_PATH_PROG([SHA1SUM],     [sha1sum],     [no])
AC_PATH_PROG([SHA256SUM],   [sha256sum],   [no])
AC_PATH_PROG([SHA512SUM],   [sha512sum],   [no])


AM_CONDITIONAL(HAVE_MD5, test ! x"$MD5SUM" = "xno")
AM_CONDITIONAL(HAVE_SHA1, test ! x"$SHA1SUM" = "xno")
AM_CONDITIONAL(HAVE_SHA256, test ! x"$SHA256SUM" = "xno")
AM_CONDITIONAL(HAVE_SHA512, test ! x"$SHA512SUM" = "xno")


if test "$CHMOD" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)

fi


if test "$RM" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)

fi


if test "$MV" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)

fi


if test "$CP" = no ; then

AC_MSG_ERROR(Install the coreutils package !, 1)

fi

# binutils package:
AC_PATH_PROG([NM], [nm], [no])

if test "$NM" = no ; then

  AC_MSG_ERROR(Install the binutils package !, 1)

fi


############### Installation of *.desktop file packages ################

# desktop-file-utils package:
AC_PATH_PROG([UPDATE_DESKTOP_DATABASE],  [update-desktop-database],   [no])
AC_PATH_PROG([DESKTOP_FILE_INSTALL],     [desktop-file-install],      [no])
# xdg-utils package:
AC_PATH_PROG([XDG_DESKTOP_MENU],         [xdg-desktop-menu],          [no])


xdg_utils=no
destop_file_utils=no


if test x"$XDG_DESKTOP_MENU" = xno ; then

  AC_MSG_WARN(Install either the xdg-utils or desktop-file-utils package !)

  AC_MSG_WARN(This is not absolutely required.)

  AC_MSG_WARN(But recommand to install desktop files.)

else

xdg_utils=yes

fi

if test x"$DESKTOP_FILE_INSTALL" = xno ; then

  AC_MSG_NOTICE(The desktop-file-install tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The desktop-file-install tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

else

desktop_file_utils=yes

fi



if test x"$XDG_DESKTOP_MENU" = xno ; then

  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)


fi

if test x"$UPDATE_DESKTOP_DATABASE" = xno ; then

  AC_MSG_NOTICE(This desktop-file-install tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

fi

AC_PATH_PROG([XDG_ICON_RESSOURCE],  [xdg-icon-resource],  [no])

if test x"$XDG_ICON_RESSOURCE" = xno ; then
 
  AC_MSG_WARN(The xdg-utils provides the way of making an *.mkp files
                    having his icon set installed and maybe used from your
                    file manager to display a *.mkp file properly.)  
 
  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

fi

AM_CONDITIONAL(HAVE_DESTOP_FILE_UTILS,        test ! x"$destop_file_utils" = "xno")
AM_CONDITIONAL(HAVE_XDG_UTILS,                test ! x"$xdg_utils" = "xno")

############### Documentation packages: ###############

MISSING_PACKAGES=

# findutils package
AC_PATH_PROG([FIND], [find], [no])

if test "${FIND}" = no ; then

AC_MSG_WARN([Install the findutils package !

   *********************** find required for mk-project *******************
   Install the findutils package from your package manager or from source.

   Or you want be able to use the some targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" findutils"

fi

# bsdmainutils
AC_PATH_PROG([HEXDUMP], [hexdump], [no])

if test "${HEXDUMP}" = no ; then

AC_MSG_WARN([Install the bsdmainutils package !

   *********************** find required for mk-project *******************
   Install the bsdmainutils package from your package manager
   or from source.

   Or you want be able to use the some targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" hexdump"

fi

# gettext package
AC_PATH_PROG([XGETTEXT], [xgettext], [no])

if test "${XGETTEXT}" = no ; then

AC_MSG_WARN([Install the gettext package !

   *********************** find required for mk-project *******************
   Install the gettext package from your package manager or from source.

   Or you want be able to use the some targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" gettext"

fi

############### Code formatters packages: ###############

# indent package
AC_PATH_PROG([INDENT], [indent], [no])

if test "${INDENT}" = no ; then

AC_MSG_WARN([Install the indent package !

   *********************** find required for mk-project *******************
   Install the indent package from your package manager or from source.

   Or you want be able to use the some targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" indent"

fi

# astyle package
AC_PATH_PROG([ASTYLE], [astyle], [no])

if test "${ASTYLE}" = no ; then

AC_MSG_WARN([Install the astyle package !

   *********************** find required for mk-project *******************
   Install the astyle package from your package manager or from source.

   Or you want be able to use the some targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" astyle"

fi

# bcpp package
AC_PATH_PROG([BCPP], [bcpp], [no])

if test "${BCPP}" = no ; then

AC_MSG_WARN([Install the bcpp package !

   *********************** find required for mk-project *******************
   Install the bcpp package from your package manager or from source.

   Or you want be able to use the some targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" bcpp"

fi


############### Distributing packages: ###############

# tar package
AC_PATH_PROG([TAR], [tar], [no])

if test "${TAR}" = no ; then

AC_MSG_WARN([Install the tar package !

   ************************ tar required for mk-project *******************
   Install the tar package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" tar"

fi

# gzip package
AC_PATH_PROG([GZIP], [gzip], [no])

if test "${GZIP}" = no ; then

AC_MSG_WARN([Install the gzip package !

   ************************ gzip required for mk-project *******************
   Install the gzip package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" gzip"

fi

# bzip2 package
AC_PATH_PROG([BZIP2], [bzip2], [no])

if test "${BZIP2}" = no ; then

AC_MSG_WARN([Install the bzip2 package !

   ************************ gzip required for mk-project *******************
   Install the bzip2 package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" bzip2"

fi

# zip package
AC_PATH_PROG([ZIP], [zip], [no])

if test "${ZIP}" = no ; then

AC_MSG_WARN([Install the zip package !

   ************************ zip required for mk-project *******************
   Install the zip package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" zip"

fi

# lzop package
AC_PATH_PROG([LZOP], [lzop], [no])

if test "${LZOP}" = no ; then

AC_MSG_WARN([Install the lzop package !

   ************************ zip required for mk-project *******************
   Install the zip package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" lzop"

fi

# rar package
AC_PATH_PROG([RAR], [rar], [no])

if test "${RAR}" = no ; then

AC_MSG_WARN([Install the rar package !

   ************************ rar required for mk-project *******************
   Install the rar package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" rar"

fi


# lzip package
AC_PATH_PROG([LZIP], [lzip], [no])

if test "${LZIP}" = no ; then

AC_MSG_WARN([Install the lzop package !

   ************************ zip required for mk-project *******************
   Install the lzop package from your package manager or from source.

   Or you want be able to use some distributing targets from mk-project !

   Then retry to launch the ./configure script...
   ************************************************************************
   ]) # Variable: ac_cv_prog_variable

MISSING_PACKAGES=${MISSING_PACKAGES}" lzip"

fi


##################################################

AC_PATH_PROG([SPHINX],    [sphinx-quickstart],   [no])

if test "$SPHINX" = no ; then

  AC_MSG_WARN(Install the python(3)-sphinx package !)

MISSING_PACKAGES=${MISSING_PACKAGES}" python(3)-sphinx"

fi

##################################################

AC_PATH_PROG([PYTHON_DOCUTILS],    [python-docutils],   [no])

if test "$PYTHON_DOCUTILS" = no ; then

  AC_MSG_WARN(Install the python-docutils package !)

fi

AC_PATH_PROG([PYTHON_DOCUTILS_3],    [python3-docutils],   [no])

if test "$PYTHON_DOCUTILS_3" = no ; then

  AC_MSG_WARN(Install the python3-docutils package !)

fi

##################################################

AC_PATH_PROG([VALGRIND],    [valgrind],   [no])

if test "$VALGRIND" = no ; then

  AC_MSG_WARN(Install the valgrind package !)

fi

##################################################

# Checks for libraries.

PKG_CHECK_MODULES([GTK], [gtk+-3.0], , AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ****************** GTK 3 library required for mk-project ***************
   Install the GTK 3 library from your package manager or from source.

   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

PKG_CHECK_MODULES([VTE], [vte-2.91], , AC_MSG_ERROR(   vte-2.91 library not detected !!!

   ***************** vte-2.91 library required for mk-project **************
   Install the vte-2.91 library from your package manager or from source.

   WARNING: Take care to install the development files from vte-2.91 !!!
            Often call: libvte-2.91-dev or libvte-2.91-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))


#if test x"$platform_darwin" = "xyes" ; then
#
#PKG_CHECK_MODULES([XML], [libxml-2.0], , AC_MSG_ERROR(   xml2 library not detected !!!
#
#   **************** libxml2 library required for mk-project ***************
#   Install the xml2 library from your package manager or from source.
#
#   WARNING: Take care to install the development files from libxml2 !!!
#            Often call: libxml2-dev or libxml2-devel.
#
#   Then retry to launch the ./configure script...
#   ************************************************************************
#   , 1))
#
#else

# This macro (m4) is not portable to MacOSX.

AM_PATH_XML2([], [], AC_MSG_ERROR(   xml2 library not detected !!!

   **************** libxml2 library required for mk-project ***************
   Install the xml2 library from your package manager or from source.

   WARNING: Take care to install the development files from libxml2 !!!
            Often call: libxml2-dev or libxml2-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))


AC_SUBST(XML_CPPFLAGS)
AC_SUBST(XML_LIBS)

# fi

PKG_CHECK_MODULES([ADWAITA_ICON_THEME], [adwaita-icon-theme], ,AC_MSG_ERROR(   adwaita-icon-theme not detected !!!

   *********** adwaita-icon-theme library required for mk-project **********
   Install the adwaita-icon-theme library from your package manager
   or from source.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

if test x"$platform_darwin" = "xyes" ; then

PKG_CHECK_MODULES([GTK_MAC_INTEGRATION], [gtk-mac-integration-gtk3], [], AC_MSG_ERROR(   gtk-mac-integration-gtk3 library not detected !!!

*** gtk-mac-integration-gtk3 library required for mk-project ***

Install the gtk-mac-integration-gtk3 library.

You can easily get it through the package manager brew on Mac OSX.

$ brew install gtk-mac-integration

Then retry to launch the ./configure script...
************************************************************************
, 1))

fi



AM_PATH_PYTHON([],[], AC_MSG_WARN(   python not detected !!!

   ********************* python required for mk-project *******************
   Install python 2 and/or 3 from your package manager or from source.

   Install the packages:

   * python

   * python-minimal

   and/or

   * python3

   * python3-minimal
            
   Then retry to launch the ./configure script...
   ************************************************************************
   ))

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h limits.h locale.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([realpath setlocale strdup strrchr])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 data/Makefile
                 texi/Makefile
                 man/Makefile
                 desktop/Makefile
                 doc/Makefile
                 MACOSX/Makefile])


AC_OUTPUT

AC_MSG_NOTICE(System check OK !!!)

echo "
  ************************ ${PACKAGE_STRING} **********************

  Package: ${PACKAGE_NAME}            Version: ${PACKAGE_VERSION}

  ${PACKAGE_NAME} a tool to ease the development process and
  a good bridge for the distributing process.

  Package dependencies: gtk-3, xml2, vte-2.91.

  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}

  Prefix: ${prefix}

  Author: Brüggemann Eddie.
  contact: ${PACKAGE_BUGREPORT}

  Missing packages: ${MISSING_PACKAGES}

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}."
