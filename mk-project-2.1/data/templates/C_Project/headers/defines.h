#ifndef %s_DEFINES_HH /** Inclusion guard **/
#define %s_DEFINES_HH

/** About definition: **/
#define AUTHOR      "%s"
#define MAIL        "<%s>"
#define PRGNAME     "%s"
#define VERSION     "%s"
#define LICENSE     "%s"
#define PRGWEBURL   "<%s>"
#define COPYRIGHT   "%s"

/** Conditional Prefix definition. **/
#ifndef PREFIX
#define ROOT
#define PREFIX ".."

/** You can define PREFIX by distributing with a preprocessor directive:
  *
  * $(MAKE) -B CPPFLAGS="-D'PREFIX=\"$(prefix)\"'"
  *
  ***********************************************************************/

#endif


/** Path definitions: **/
#ifdef ROOT
#define DATADIR                 PREFIX  "/share/" PRGNAME
#else
#define DATADIR                 PREFIX "/"
#endif


/** Example definition based on DATADIR and so PREFIX
  *
  * #define PATH_TO_ICON            DATADIR "/icons/prgname.png"
  *
  *
  * @Info: You don't have a make a define for every file:
  *        simply concatenate the define and the differents filenames.
  *
  * #define PATH_TO_MENU_ICON       DATADIR "/icons/16x16"
  *
  * #define PATH_TO_BUTTON_ICON     DATADIR "/icons/24x24"
  *
  *
  * #define PATH_TO_README          DATADIR "/README"
  *
  * #define PATH_TO_LICENSE_TEXT    DATADIR "/license/" "license.txt"
  *
  * #define PATH_TO_LICENSE_HTML    DATADIR "/license/" "license.html"
  *
  **********************************************************************/


/** Uncomment to use gettext
#define GETTEXT_SUPPORT */

#ifdef GETTEXT_SUPPORT
#include <libintl.h>

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

#define _(String) gettext       (String)
#define gettext_noop(String)     String
#define N_(String) gettext_noop (String)

#endif /* GETTEXT_SUPPORT */


/** Uncomment to use debug features or use the target: make ddebug
#define DEBUG */

#ifdef DEBUG

#include <stdio.h>

#define DEBUG_PT          fprintf(stderr,"\n%%s:%%s(...) at line: %%d\n", __FILE__, __func__, __LINE__) ;
#define DEBUG_FUNC_MARK   fprintf(stderr,"\n%%s:%%s(...) called\n",__FILE__, __func__) ;

#define DEBUG_INT(x)      fprintf(stderr,"DEBUG PT N° %%d\n",   (x)) ;
#define DEBUG_LINT(x)     fprintf(stderr,"DEBUG PT N° %%d\n",   (x)) ;
#define DEBUG_LLINT(x)    fprintf(stderr,"DEBUG PT N° %%d\n",   (x)) ;

#define DEBUG_FLOAT(x)    fprintf(stderr,"DEBUG PT N° %%f\n",   (x)) ;
#define DEBUG_DOUBLE(x)   fprintf(stderr,"DEBUG PT N° %%lf\n",  (x)) ;
#define DEBUG_LDOUBLE(x)  fprintf(stderr,"DEBUG PT N° %%llf\n", (x)) ;

#define DEBUG_STR(str)    fprintf(stderr,"%%s\n", (str)) ;
#define DEBUG_PTR(ptr)    fprintf(stderr,"%%p\n", (ptr)) ;


/** Extended DEBUGGING **/
#define EDEBUG_INT(str, x)      fprintf(stderr,"%%s(line:%%d): %%s %%d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LINT(str, x)     fprintf(stderr,"%%s(line:%%d): %%s %%d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LLINT(str, x)    fprintf(stderr,"%%s(line:%%d): %%s %%d\n",   __func__, __LINE__, (str), (x)) ;

#define EDEBUG_FLOAT(str, x)    fprintf(stderr,"%%s(line:%%d): %%s %%f\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_DOUBLE(str, x)   fprintf(stderr,"%%s(line:%%d): %%s %%lf\n",  __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LDOUBLE(str, x)  fprintf(stderr,"%%s(line:%%d): %%s %%llf\n", __func__, __LINE__, (str), (x)) ;

#define EDEBUG_STR(str)         fprintf(stderr,"%%s(%%d): %%s\n", __func__, __LINE__, (str)) ;
#define EDEBUG_PTR(ptr)         fprintf(stderr,"%%s(%%d): %%p\n", __func__, __LINE__, (ptr)) ;

#endif




#endif /** Inclusion guard **/
