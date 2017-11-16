#include <limits.h>
#include <float.h>
#include <stdio.h>

int main(void) {
 
  #ifdef __STDV__
  #if __STDC__
  fprintf(stdout,"Compiler and C libraries Conform to ISO C STANDART\n") ;
  #else
  fprintf(stdout,"Compiler and C libraries NOT Conform to ISO C STANDART\n") ;
  #endif
  #endif
 
  #ifdef __STDC_VERSION__
  #if __STDC_VERSION__
  fprintf(stdout,"C STANDART version: %li (yyyyymm)\n",  __STDC_VERSION__) ;
  #endif
  #endif
 
  #ifdef __STDC_HOSTED__
  #if __STDC_HOSTED__
  fprintf(stdout,"C STD library hosted (complete implementation of the libc)\n") ;
  #endif
  #endif
 
  #ifdef __STDC_IEC_559__
  #if __STDC_IEC_559__
  fprintf(stdout,"Conform to IEC 605559 floating point arithmetic\n"  ) ;
  #endif
  #endif

  #ifdef __STDC_NO_COMPLEX__
  #if __STDC_NO_COMPLEX__
  fprintf(stdout,"Cannot use <complex.h>\n") ;
  #else
  fprintf(stdout,"Can use <complex.h>\n") ;
  #endif
  #endif

  #ifdef __STDC_IEC_559_COMPLEX__
  #if __STDC_IEC_559_COMPLEX__
  fprintf(stdout,"Complex numbers IEC 60559 compatible\n"  ) ;
  #else
  fprintf(stdout,"Complex numbers NOT IEC 60559 compatible\n"  ) ;
  #endif
  #endif
 
 
 
  #ifdef __STDC_ANALYZABLE__
  #if __STDC_ANALYZABLE__
  fprintf(stdout,"Implementation conform to Appendix L from the standart\n") ;
  #endif
  #endif
 
  #ifdef __STDC_UTF_16__
  #if __STDC_UTF_16__
  fprintf(stdout,"char16_t UTF-16 encoded\n") ;
  #else
  fprintf(stdout,"char16_t NOT UTF-16 encoded\n") ;
  #endif
  #endif

  #ifdef __STDC_UTF_32__
  #if __STDC_UTF_32__
  fprintf(stdout,"char32_t UTF-32 encoded\n") ;
  #else
  fprintf(stdout,"char32_t NOT UTF-32 encoded\n") ;
  #endif
  #endif

  #ifdef __STDC_MB_MIGHT_NEQ_WC__
  #if __STDC_MB_MIGHT_NEQ_WC__
  fprintf(stdout,"Basic char set have different values into wchar_t\n") ;
  #else
  fprintf(stdout,"Basic char set have equal values into wchar_t\n") ;
  #endif
  #endif

  #ifdef __STDC_ISO_10646__
  #if __STDC_ISO_10646__
  fprintf(stdout,"Every character in the unicode required\nwhen represented as a wchar_t,\nthe same value as the short identifier.\n__STDC_ISO_10646__ = %li (yyyyymm)\n",__STDC_ISO_10646__) ;
  #endif
  #endif

  #ifdef __STDC_NO_ATOMICS__
  #if __STDC_NO_ATOMICS__
  fprintf(stdout,"Cannot use <stdatomic.h>\n") ;
  #else
  fprintf(stdout,"Can use <stdatomic.h>\n") ;
  #endif
  #endif

  #ifdef __STDC_NO_THREADS__
  #if __STDC_NO_THREADS__
  fprintf(stdout,"Cannot use <threads.h>\n") ;
  #else
  fprintf(stdout,"Can use <threads.h>\n") ;
  #endif
  #endif
 
  #ifdef __STDC_NO_VLA__
  #if __STDC_NO_VLA__
  fprintf(stdout,"Implementation does not support variable length arrays.\n") ;
  #endif
  #endif
 
  #ifdef __STDC_LIB_EXT1__
  #if __STDC_LIB_EXT1__
  fprintf(stdout,"Implementation supports Appendix K in the standart on bounds checking library interface.\n__STDC_LIB_EXT1__ = %li (yyyyymm)\n", __STDC_LIB_EXT1__) ;
  #endif
  #endif
 
  fprintf(stdout,"A byte have %d bits\n", CHAR_BIT) ;

  fprintf(stdout,"FLT_RADIX (radix of exponent): %d\n", FLT_RADIX) ;

  fprintf(stdout,"FLT_MANT_DIG  (number of radix 'r' significant bits): %i\n",  FLT_MANT_DIG) ;
  fprintf(stdout,"DBL_MANT_DIG  (number of radix 'r' significant bits): %i\n",  DBL_MANT_DIG) ;
  fprintf(stdout,"LDBL_MANT_DIG (number of radix 'r' significant bits): %i\n",  LDBL_MANT_DIG) ;

  fprintf(stdout,"FLT_DIG  (nb of significant digits by rounding): %i\n", FLT_DIG) ;
  fprintf(stdout,"DBL_DIG  (nb of significant digits by rounding): %i\n", DBL_DIG) ;
  fprintf(stdout,"LDBL_DIG (nb of significant digits by rounding): %i\n", LDBL_DIG) ;

  fprintf(stdout,"FLT_MIN_EXP  (min nb of n such as r(n-1) is a normalize nb): %i\n", FLT_MIN_EXP) ;
  fprintf(stdout,"DBL_MIN_EXP  (min nb of n such as r(n-1) is a normalize nb): %i\n", DBL_MIN_EXP) ;
  fprintf(stdout,"LDBL_MIN_EXP (min nb of n such as r(n-1) is a normalize nb): %i\n", LDBL_MIN_EXP) ;

  fprintf(stdout,"FLT_MAX_EXP  (min nb of n such as r(n-1) is a normalize nb): %i\n", FLT_MAX_EXP) ;
  fprintf(stdout,"DBL_MAX_EXP  (min nb of n such as r(n-1) is a normalize nb): %i\n", DBL_MAX_EXP) ;
  fprintf(stdout,"LDBL_MAX_EXP (min nb of n such as r(n-1) is a normalize nb): %i\n", LDBL_MAX_EXP) ;

  fprintf(stdout,"FLT_MIN  (min representable finite floating-point value): %f\n", FLT_MIN) ;
  fprintf(stdout,"DBL_MIN  (min representable finite floating-point value): %lf\n", DBL_MIN) ;
  fprintf(stdout,"LDBL_MIN (min representable finite floating-point value): %Lf\n", LDBL_MIN) ;

  fprintf(stdout,"FLT_MAX  (max representable finite floating-point value): %E\n", FLT_MAX) ;
  fprintf(stdout,"DBL_MAX  (max representable finite floating-point value): %E\n", DBL_MAX) ;
  fprintf(stdout,"LDBL_MAX (max representable finite floating-point value): %LE\n", LDBL_MAX) ;
 
  #ifdef __DATE__
  #ifdef __TIME__
  fprintf(stdout,"\nImplementation dump done the %s at %s\n", __DATE__, __TIME__) ;
  #endif
  #endif
  

  return 0 ;
}

