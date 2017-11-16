#ifndef STD_DEFINITION_INFO_HH  /** Inclusion guard **/
#define STD_DEFINITION_INFO_HH

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


#endif /** Inclusion guard **/