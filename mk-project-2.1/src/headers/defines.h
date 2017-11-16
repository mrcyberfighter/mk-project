/** ***********************************************************************************
  *                                                                                   *
  * mk-project a tool to ease the development process                                 *
  * and a good bridge for the distributing process.                                   *
  *                                                                                   *
  * Copyright (C) 2016,2017 Brüggemann Eddie                                          *
  *                                                                                   *
  * This file is part of mk-project.                                                  *
  * mk-project is free software: you can redistribute it and/or modify                *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * mk-project is distributed in the hope that it will be useful,                     *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with mk-project. If not, see <http://www.gnu.org/licenses/>                 *
  *                                                                                   *
  *************************************************************************************/

#ifndef MK_PROJECT_DEFINES_HH /** Inclusion guard **/
#define MK_PROJECT_DEFINES_HH


/* #define _POSIX_SOURCE */
/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro, then the functionality from the POSIX.1
  * standard (IEEE Standard 1003.1) is available, as well as all of the
  * ISO C facilities.
  *
  * The state of '_POSIX_SOURCE' is irrelevant if you define the macro
  * '_POSIX_C_SOURCE' to a positive integer.
  *
  **********************************************************************/


/* #define _POSIX_C_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  *  Define this macro to a positive integer to control which POSIX
  *  functionality is made available.  The greater the value of this
  *  macro, the more functionality is made available.
  *
  *  If you define this macro to a value greater than or equal to '1',
  *  then the functionality from the 1990 edition of the POSIX.1
  *  standard (IEEE Standard 1003.1-1990) is made available.
  *
  *  If you define this macro to a value greater than or equal to '2',
  *  then the functionality from the 1992 edition of the POSIX.2
  *  standard (IEEE Standard 1003.2-1992) is made available.
  *
  *  If you define this macro to a value greater than or equal to
  *  '199309L', then the functionality from the 1993 edition of the
  *  POSIX.1b standard (IEEE Standard 1003.1b-1993) is made available.
  *
  *  Greater values for '_POSIX_C_SOURCE' will enable future extensions.
  *  The POSIX standards process will define these values as necessary,
  *  and the GNU C Library should support them some time after they
  *  become standardized.  The 1996 edition of POSIX.1 (ISO/IEC 9945-1:
  *  1996) states that if you define '_POSIX_C_SOURCE' to a value
  *  greater than or equal to '199506L', then the functionality from the
  *  1996 edition is made available.
  *
  ***********************************************************************/

/* #define _BSD_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro, functionality derived from 4.3 BSD Unix
  * is included as well as the ISO C, POSIX.1, and POSIX.2 material.
  *
  ********************************************************************/

/* #define _SVID_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro, functionality derived from SVID is
  * included as well as the ISO C, POSIX.1, POSIX.2, and X/Open
  * material.
  *
  **************************************************************/

/* #define _XOPEN_SOURCE */
/* #define _XOPEN_SOURCE_EXTENDED */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro, functionality described in the X/Open
  * Portability Guide is included.  This is a superset of the POSIX.1
  * and POSIX.2 functionality and in fact '_POSIX_SOURCE' and
  * '_POSIX_C_SOURCE' are automatically defined.
  *
  * As the unification of all Unices, functionality only available in
  * BSD and SVID is also included.
  *
  * If the macro '_XOPEN_SOURCE_EXTENDED' is also defined, even more
  * functionality is available.  The extra functions will make all
  * functions available which are necessary for the X/Open Unix brand.
  *
  * If the macro '_XOPEN_SOURCE' has the value 500 this includes all
  * functionality described so far plus some new definitions from the
  * Single Unix Specification, version 2.
  *
  ********************************************************************/

/* #define _LARGEFILE_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If this macro is defined some extra functions are available which
  * rectify a few shortcomings in all previous standards.
  * Specifically, the functions 'fseeko' and 'ftello' are available.
  * Without these functions the difference between the ISO C interface
  * ('fseek', 'ftell') and the low-level POSIX interface ('lseek')
  * would lead to problems.
  *
  * This macro was introduced as part of the Large File Support
  * extension (LFS).
  *
  ******************************************************************/

/* #define _LARGEFILE64_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro an additional set of functions is made
  * available which enables 32 bit systems to use files of sizes beyond
  * the usual limit of 2GB. This interface is not available if the
  * system does not support files that large.  On systems where the
  * natural file size limit is greater than 2GB (i.e., on 64 bit
  * systems) the new functions are identical to the replaced functions.
  *
  * The new functionality is made available by a new set of types and
  * functions which replace the existing ones.  The names of these new
  * objects contain '64' to indicate the intention, e.g., 'off_t' vs.
  * 'off64_t' and 'fseeko' vs.  'fseeko64'.
  *
  * This macro was introduced as part of the Large File Support
  * extension (LFS). It is a transition interface for the period when 64 bit
  * offsets are not generally used (see '_FILE_OFFSET_BITS').
  *
  *****************************************************************************/

/* #define _FILE_OFFSET_BITS */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * This macro determines which file system interface shall be used,
  * one replacing the other.  Whereas '_LARGEFILE64_SOURCE' makes the 64 bit
  * interface available as an additional interface, '_FILE_OFFSET_BITS'
  * allows the 64 bit interface to replace the old interface.
  *
  * If '_FILE_OFFSET_BITS' is undefined, or if it is defined to the
  * value '32', nothing changes.  The 32 bit interface is used and
  * types like 'off_t' have a size of 32 bits on 32 bit systems.
  *
  * If the macro is defined to the value '64', the large file interface
  * replaces the old interface.  I.e., the functions are not made
  * available under different names (as they are with
  * '_LARGEFILE64_SOURCE').  Instead the old function names now
  * reference the new functions, e.g., a call to 'fseeko' now indeed
  * calls 'fseeko64'.
  *
  * This macro should only be selected if the system provides
  * mechanisms for handling large files.  On 64 bit systems this macro
  * has no effect since the '*64' functions are identical to the normal
  * functions.
  *
  * This macro was introduced as part of the Large File Support
  * extension (LFS).
  *
  ****************************************************************************/

/* #define _ISOC99_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * Until the revised ISO C standard is widely adopted the new features
  * are not automatically enabled.  The GNU C Library nevertheless has
  * a complete implementation of the new standard and to enable the new
  * features the macro '_ISOC99_SOURCE' should be defined.
  *
  **********************************************************************/

/* #define _GNU_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro, everything is included: ISO C89, ISO C99,
  * POSIX.1, POSIX.2, BSD, SVID, X/Open, LFS, and GNU extensions.  In
  * the cases where POSIX.1 conflicts with BSD, the POSIX definitions
  * take precedence.
  *
  **********************************************************************/

/* #define _DEFAULT_SOURCE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define this macro, most features are included apart from
  * X/Open, LFS and GNU extensions; the effect is similar to defining
  * '_POSIX_C_SOURCE' to '200809L' and '_POSIX_SOURCE', '_SVID_SOURCE',
  * and '_BSD_SOURCE' to 1.  Defining this macro, on its own and
  * without using compiler options such as '-ansi' or '-std=c99', has
  * the same effect as not defining any feature test macros; defining
  * it together with other feature test macros, or when options such as
  * '-ansi' are used, enables those features even when the other
  * options would otherwise cause them to be disabled.
  *
  *********************************************************************/

/* #define _REENTRANT   */
/* #define _THREAD_SAFE */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * If you define one of these macros, reentrant versions of several
  * functions get declared.  Some of the functions are specified in
  * POSIX.1c but many others are only available on a few other systems
  * or are unique to the GNU C Library.  The problem is the delay in
  * the standardization of the thread safe C library interface.
  *
  * Unlike on some other systems, no special version of the C library
  * must be used for linking.  There is only one version but while
  * compiling this it must have been specified to compile as thread
  * safe.
  *
  ********************************************************************/

/* Final word */

/** extract of $ info libc (node: 1.3.4 Feature Test Macros)
  *
  * We recommend you use '_GNU_SOURCE' in new programs.  If you don't
  * specify the '-ansi' option to GCC, or other conformance options such as
  * '-std=c99', and don't define any of these macros explicitly, the effect
  * is the same as defining '_DEFAULT_SOURCE' to 1.
  *
  * When you define a feature test macro to request a larger class of
  * features, it is harmless to define in addition a feature test macro for
  * a subset of those features.  For example, if you define
  * '_POSIX_C_SOURCE', then defining '_POSIX_SOURCE' as well has no effect.
  * Likewise, if you define '_GNU_SOURCE', then defining either
  * '_POSIX_SOURCE' or '_POSIX_C_SOURCE' or '_SVID_SOURCE' as well has no
  * effect.
  *
  ************************************************************************/




/** About definition: **/
#define AUTHOR      "Brüggemann Eddie"
#define MAIL        "<mrcyberfighter@gmail.com>"
#define PRGNAME     "mk-project"
#define VERSION     "2.1"
#define LICENSE     "GPLv3"
#define PRGWEBURL   "http://www.open-source-projects.net/mk-project/mk-project"
#define COPYRIGHT   "2016-2017 (C) Eddie Brüggemann"

/** Conditional Prefix definition. **/
#ifndef PREFIX
#define ROOT
#define PREFIX ".."
#endif


/** Path definitions: **/
#ifdef ROOT
#define DATADIR                 PREFIX "/"
#else
#define DATADIR                 PREFIX "/share" "/" PRGNAME
#endif


#define PATH_TO_ICON            DATADIR "/icons/mk-project_icon.png"

#define PATH_TO_MENU_ICON       DATADIR "/icons/16x16/"

#define PATH_TO_BUTTON_ICON     DATADIR "/icons/22x22/"

#define PATH_TO_README          DATADIR "/README"


#define PATH_TO_LICENSE_TEXT    DATADIR "/license/" "gpl.txt"

#define PATH_TO_LICENSE_HTML    DATADIR "/license/" "gpl.html"

#define PATH_TO_CONF_FILE       DATADIR "/configuration/mk-project_configuration.ini"

#define PATH_TO_HTML_NOTICE     DATADIR "/documentation/notice/index.html"

/** Licensing boilerplate files **/

#define PATH_TO_TEMPLATE        DATADIR "/templates"

#define PATH_TO_LICENSING       PATH_TO_TEMPLATE   "/license"

#define PATH_TO_LICENSING_AGPL        PATH_TO_LICENSING  "/agpl.tmpl"
#define PATH_TO_LICENSING_GPL         PATH_TO_LICENSING  "/gpl.tmpl"
#define PATH_TO_LICENSING_FDL         PATH_TO_LICENSING  "/fdl.tmpl"
#define PATH_TO_LICENSING_LGPL        PATH_TO_LICENSING  "/lgpl.tmpl"
#define PATH_TO_LICENSING_APACHE_2_0  PATH_TO_LICENSING  "/Apache_2.0.tmpl"
#define PATH_TO_LICENSING_CLEAR_BSD   PATH_TO_LICENSING  "/ClearBSD.tmpl"
#define PATH_TO_LICENSING_FREE_BSD    PATH_TO_LICENSING  "/FreeBSD.tmpl"

#define PATH_TO_LICENSES_FOLDER       PATH_TO_TEMPLATE   "/licenses"

#define PATH_TO_LICENSE_FOLDER_AGPL         PATH_TO_LICENSES_FOLDER    "/agpl"
#define PATH_TO_LICENSE_FOLDER_GPL          PATH_TO_LICENSES_FOLDER    "/gpl"
#define PATH_TO_LICENSE_FOLDER_FDL          PATH_TO_LICENSES_FOLDER    "/fdl"
#define PATH_TO_LICENSE_FOLDER_LGPL         PATH_TO_LICENSES_FOLDER    "/lgpl"

#define PATH_TO_LICENSE_FOLDER_APACHE_2_0   PATH_TO_LICENSES_FOLDER    "/Apache_2.0"
#define PATH_TO_LICENSE_FOLDER_CLEAR_BSD    PATH_TO_LICENSES_FOLDER    "/Clear_BSD"
#define PATH_TO_LICENSE_FOLDER_FREE_BSD     PATH_TO_LICENSES_FOLDER    "/Free_BSD"

/** *.desktop file boilerplate **/
#define PATH_TO_DESKTOP_TEMPLATE              PATH_TO_TEMPLATE "/desktop" "/desktop.tmpl"



/** C project path defines **/
#define PATH_TO_C_DEFINES_H_TEMPLATE          PATH_TO_TEMPLATE "/C_Project" "/headers" "/defines.h"

#define PATH_TO_C_INCLUDES_H_TEMPLATE         PATH_TO_TEMPLATE "/C_Project" "/headers" "/includes.h"

#define PATH_TO_C_GLOBAL_VARS_C_TEMPLATE      PATH_TO_TEMPLATE "/C_Project" "/global_vars.c"

#define PATH_TO_C_GLOBAL_VARS_H_TEMPLATE      PATH_TO_TEMPLATE "/C_Project" "/global_vars.h"

#define PATH_TO_C_MAIN_TEMPLATE               PATH_TO_TEMPLATE "/C_Project" "/main.c"

#define PATH_TO_C_LIB_C_TEMPLATE              PATH_TO_TEMPLATE "/C_Project" "/lib"      "/libprint_it.c"

#define PATH_TO_C_LIB_H_TEMPLATE              PATH_TO_TEMPLATE "/C_Project" "/lib"      "/libprint_it.h"





/** C++ project path defines **/
#define PATH_TO_CXX_DEFINES_H_TEMPLATE        PATH_TO_TEMPLATE "/CXX_Project" "/headers" "/defines.h"

#define PATH_TO_CXX_INCLUDES_H_TEMPLATE       PATH_TO_TEMPLATE "/CXX_Project" "/headers" "/includes.h"

#define PATH_TO_CXX_GLOBAL_VARS_C_TEMPLATE    PATH_TO_TEMPLATE "/CXX_Project" "/global_vars.c"

#define PATH_TO_CXX_GLOBAL_VARS_H_TEMPLATE    PATH_TO_TEMPLATE "/CXX_Project" "/global_vars.h"

#define PATH_TO_CXX_MAIN_TEMPLATE             PATH_TO_TEMPLATE "/CXX_Project" "/main.c"

#define PATH_TO_CXX_LIB_C_TEMPLATE            PATH_TO_TEMPLATE "/CXX_Project" "/lib"      "/libprint_it.cpp"

#define PATH_TO_CXX_LIB_H_TEMPLATE            PATH_TO_TEMPLATE "/CXX_Project" "/lib"      "/libprint_it.h"


/** Makefile template filepath **/
#define PATH_TO_MAIN_MAKEFILE_TEMPLATE    PATH_TO_TEMPLATE  "/C_CXX_Project"  "/Makefile"

#define PATH_TO_FMT_CODE_MK_TEMPLATE      PATH_TO_TEMPLATE  "/C_CXX_Project"  "/subMakefiles" "/code_formatter.mk"

#define PATH_TO_DIST_MK_TEMPLATE          PATH_TO_TEMPLATE  "/C_CXX_Project"  "/subMakefiles" "/distributing.mk"

#define PATH_TO_DOC_MK_TEMPLATE           PATH_TO_TEMPLATE  "/C_CXX_Project"  "/subMakefiles" "/documentation.mk"

#define PATH_TO_BIN_CHECK_MK_TEMPLATE     PATH_TO_TEMPLATE  "/C_CXX_Project"  "/subMakefiles" "/binary_checks.mk"

#define PATH_TO_PATH_MK_TEMPLATE          PATH_TO_TEMPLATE  "/C_CXX_Project"  "/subMakefiles" "/path.mk"

#define PATH_TO_PATH_LIB_MK_TEMPLATE      PATH_TO_TEMPLATE  "/C_CXX_Project"  "/lib"          "/Makefile"

#define PATH_TO_SPHINX_SHOW_MK            PATH_TO_TEMPLATE  "/C_CXX_Project"  "/subMakefiles" "/sphinx-show.mk"

/** Scripts path defines  **/
#define PATH_TO_PREPEND_LICENSE_FILE      PATH_TO_TEMPLATE  "/scripts"        "/prepend_license.py"


#define PATH_TO_C_CXX_PROJECT_README      PATH_TO_TEMPLATE  "/C_CXX_Project"  "/README.html"

//#undef  PATH_TO_C_CXX_PROJECT_README
//#define PATH_TO_C_CXX_PROJECT_README      PATH_TO_TEMPLATE  "/C_CXX_Project"  "/README.rst"

#define PATH_TO_C_CXX_LIB_README          PATH_TO_TEMPLATE  "/C_CXX_Project"  "/lib" "/README.rst"

#if 0
/** Python projects no more supported ! **/

/** Python project path defines: **/
#define PATH_TO_PYTHON_MAKEFILE           PATH_TO_TEMPLATE "/Py_Project"    "/Makefile"

#define PATH_TO_PYTHON_FMT_CODE           PATH_TO_TEMPLATE "/Py_Project"    "/subMakefiles" "/code_formatter.mk"

#define PATH_TO_PYTHON_MAIN_SCRIPT        PATH_TO_TEMPLATE "/Py_Project"    "/mk-project.py"

#define PATH_TO_PINDENT_SCRIPT            PATH_TO_TEMPLATE "/Py_Project"    "/pindent.py"
#endif

/** Image path **/
#define PATH_TO_IMAGE           DATADIR "/icons/"

#define PATH_TO_BIN_FOLDER      PREFIX  "/bin"

#define PATH_TO_MK_PROJECT      PREFIX  "/bin/"  PRGNAME



#define COMPILER_ENTRY_SIZE (64*6)

#define BOX_SPACING (32)



/** Simple check and free macro. **/
#define SEC_FREE(ptr) { g_free(ptr) ; ptr = NULL ; } ;


/** gettext support enabled **/
#define GETTEXT_SUPPORT


/** gettext support: **/
#ifdef GETTEXT_SUPPORT
#include <glib/gi18n.h>
#include <locale.h>

#ifdef ROOT

#ifdef  PACKAGE
#undef  PACKAGE
#endif

#define PACKAGE    "./"   PRGNAME


#ifdef  LOCALEDIR
#undef  LOCALEDIR
#endif

#else

#define PACKAGE  PREFIX "/bin" "/" PRGNAME

#endif /* ROOT */

#define LOCALEDIR  PREFIX "/share" "/locale"

//#define _(String) gettext       (String)
//#define gettext_noop(String)     String
//#define N_(String) gettext_noop (String)

#endif /* GETTEXT_SUPPORT */



#ifdef TRIBOOL                 /**  The idea is to make a trilogic boolean type. **/
#include <stdint.h>

/** This work is an artistic try from a young newbie into the
  *
  *  deep "beat the (ISO) standard" subject.
  *
  ***********************************************************/


/**  This doesn't really make sens but we can do this
  *  in assembly with (a one or two) bit test feature...
  *
  *  If you don't get interest in my idea, simply erase
  *  this on the other hand contact me,
  *
  *  at mail address: <mrcyberfighter@gmail>
  *
  *****************************************************/

/** We can simply defines our triboolean types like this: **/
typedef int_least8_t tbool;

tbool tb_minus  =  -1   ;             
tbool tb_none   =   0   ;
tbool tb_plus   =   1   ;

/** ************************************************************************ **/

/** Or we can defines our triboolean types like this:

@NOTE: Recently I've improved the concept of the triboolean types like this:
       It were nice from you if you simply tell me which art of type defining
       is the best. Thanks !

       And I've learn in this time about the existents into libboost of the triboolean type.


struct tbool {

  const uint_least8_t const tb_minus  : 3 ;  // @bit_1 == 0 : @bit_2 == 1 (sign bit).
  const uint_least8_t const tb_none   : 1 ;  // @bit_1 == 0 ; @bit_2 == 0 (sign bit).
  const uint_least8_t const tb_plus   : 1 ;  // @bit_1 == 1 ; @bit_2 == 0 (sign bit).

} tbool = { .tb_minus=2, .tb_none=0, .tb_plus=1} ;

#define tb_minus  tbool.tb_minus
#define tb_none   tbool.tb_none
#define tb_plus   tbool.tb_plus

typedef uint_least8_t tb_bool ;

******************************************************/


/** A trilogical value should be defined on 2 bits like this:
  *
  * @name     @bit_1 (value bit)  @bit_2 (sign bit)   @Comment
  *
  * @tb_none     0                  0                   A none (null value) doesn't get a sign. or yes reserved for future use, we will C.
  *
  * @tb_minus    0                  1                   A negative value get a sign. And the value is equal to 0 for @minus @plus switching.
  *
  * @tb_plus     1                  0                   A positive value get no sign.
  *
  *
  * # The last possiblity: the sign bit (bit_2) rest to explore: tb_sign = "11" ;
  *
  ******************************************************************************************************************************************/





/** The control of the value of a trilogical value can be read (access or checked) like this:
  *
  * Pseudo-code ( '#' is the  one line comment sign.  )
  *
  * @if bit_2 ;                                                                                 # @bit_2 == 1
  *
  *     then : value @equal to @tb_minus    ;                                                   # @bit_1 == 1 and @bit_2 == 1 ; # Only negative values get a sign.
  *
  *
  *      # "This seems to make sens because only negative values get a sign and not positive nor null values..."
  *
  *      # "Must @not check the second bit." @AND "End up in a one pass check."
  *
  * @else ;                                                                                     # @bit_1 == 0
  *
  *   @if bit_1 ;                                                                               # @bit_1 == 1
  *
  *     then : value @equal to  @tb_plus  ;                                                     # @bit_1 == 1 and @bit_2 == 0
  *
  *   @else ;                                                                                   # @bit_1 == 0
  *
  *     then : value @equal to @tb_none   ;                                                     # @bit_1 == 0 and @bit_2 == 0
  *
  *****************************************
  *
  * The control of the value of a trilogical value can be read (access or checked) like this:
  *
  * @if bit_1 ;                                                                                 # @bit_1 == 1
  *
  *     then : value @equal to @tb_plus ;                                                       # @bit_1 == 1 and @bit_2 == 1 ; # Only a positive value get a value.
  *
  *
  *       # "This seems to make sens because only positive values are absolute positive..."
  *
  *       # "Must @not check the second bit." @AND "End up in a one pass check."
  *
  * @else ;                                                                                     # @bit_1 == 0
  *
  *   @if bit_2 ;                                                                               # @bit_2 == 1
  *
  *     then : value @equal to @tb_plus   ;                                                     # @bit_1 == 0 and @bit_2 == 1
  *
  *   @else ;                                                                                   # @bit_2 == 0
  *
  *     then : value @equal to @tb_none   ;                                                     # @bit_1 == 1 and @bit_2 == 1
  *
  *****************************************/           

/** @NOTE: The sign bit should be the second bit into the byte,
  *        instead of the last bit into the byte.
  *        For the sake of fast access with a bit test function improvement !
  *        So that the bit test operation has not to go to the byte end,
  *        instead it has simply to test the next byte instead.
  *
  ****************************************************************************/

/** Triboolean logical rules:

    @AND

    tb_minus  @and  tb_minus  =   tb_minus  ;
    tb_minus  @and  tb_none   =   tb_minus  ;
    tb_minus  @and  tb_plus   =   tb_plus   ;

    tb_plus   @and  tb_minus  =   tb_none   ;
    tb_plus   @and  tb_none   =   tb_plus   ;
    tb_plus   @and  tb_plus   =   tb_plus   ;

    tb_none   @and  tb_minus  =   tb_minus  ;
    tb_none   @and  tb_none   =   tb_none   ;
    tb_none   @and  tb_plus   =   tb_plus   ;


    @OR

    tb_minus  @or   tb_minus  =   tb_minus  ;
    tb_minus  @or   tb_none   =   tb_minus  ;
    tb_minus  @or   tb_plus   =   tb_none   ;

    tb_plus   @or   tb_minus  =   tb_none   ;
    tb_plus   @or   tb_none   =   tb_plus   ;
    tb_plus   @or   tb_plus   =   tb_plus   ;

    tb_none   @or   tb_minus  =   tb_minus  ;
    tb_none   @or   tb_none   =   tb_none   ;
    tb_none   @or   tb_plus   =   tb_plus   ;


    @XOR (OR eXclusiv: change the terms of 2 identical operators @or operation result).

    tb_minus  @xor  tb_minus  =   tb_none   ;
    tb_minus  @xor  tb_none   =   tb_minus  ;
    tb_minus  @xor  tb_plus   =   tb_none   ;

    tb_plus   @xor  tb_minus  =   tb_none   ;
    tb_plus   @xor  tb_none   =   tb_plus   ;
    tb_plus   @xor  tb_plus   =   tb_none   ;

    tb_none   @xor  tb_minus  =   tb_minus  ;
    tb_none   @xor  tb_none   =   tb_none   ;
    tb_none   @xor  tb_plus   =   tb_plus   ;

*/




#endif


#ifdef DEBUG

#include <stdio.h>

#define DEBUG_PT          fprintf(stderr,"\n%s:%s(...) at line: %d\n", __FILE__, __func__, __LINE__) ;

#define DEBUG_INT(x)      fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;
#define DEBUG_LINT(x)     fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;
#define DEBUG_LLINT(x)    fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;

#define DEBUG_FLOAT(x)    fprintf(stderr,"DEBUG PT N° %f\n",   (x)) ;
#define DEBUG_DOUBLE(x)   fprintf(stderr,"DEBUG PT N° %lf\n",  (x)) ;
#define DEBUG_LDOUBLE(x)  fprintf(stderr,"DEBUG PT N° %llf\n", (x)) ;

#define DEBUG_STR(str)          fprintf(stderr,"%s\n", (str)) ;
#define DEBUG_PTR(ptr)          fprintf(stderr,"%p\n", (ptr)) ;


/** Extended DEBUGGING **/
#define EDEBUG_INT(str, x)      fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LINT(str, x)     fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LLINT(str, x)    fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;

#define EDEBUG_FLOAT(str, x)    fprintf(stderr,"%s(line:%d): %s %f\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_DOUBLE(str, x)   fprintf(stderr,"%s(line:%d): %s %lf\n",  __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LDOUBLE(str, x)  fprintf(stderr,"%s(line:%d): %s %llf\n", __func__, __LINE__, (str), (x)) ;

#define EDEBUG_STR(str)         fprintf(stderr,"%s(%d): %s\n", __func__, __LINE__, (str)) ;
#define EDEBUG_PTR(ptr)         fprintf(stderr,"%s(%d): %p\n", __func__, __LINE__, (ptr)) ;

#define DEBUG_FUNC_MARK         fprintf(stderr,"\n%s:%s(...) called\n",__FILE__, __func__) ;

#endif




#endif /** Inclusion guard **/
