#ifndef OPTMIZE_BOOL_HH
#define OPTMIZE_BOOL_HH

#include <stdint.h>


/** This work is an artistic try from a young newbie into the
  * 
  * deep "beat the (ISO) standart" subject.
  *
**/   

struct s_bool {

  /**
    *    The usage of a structure is to make usage of bit-fields.
    *
    *    The usage of the unsigned int is for using only 1 bit otherwise (signed) we would need 2 bits.
    *
    *    Unfortunaly we cannot use a union for memory saving because
    *    their actually no compatibilty with the type bool that I can implement in this try.
    *
    **************************************************************************************************/

  const uint_least8_t const sfalse : 1 ;

  const uint_least8_t const strue  : 1 ;

} sbool = { .sfalse=0, .strue=1} ;



#define ofalse sbool.sfalse
#define otrue sbool.strue

/** No need to define a new type for our "Optimize" "otrue" and "ofalse" values which weight only 1 bit !

    The eventualy padding isn't taking into account.
 
    simply use it like this:
 
    bool var0 = ofalse ; // Why not rename ofalse into "zero".
    bool var1 = otrue ;  // And otrue into "one". It would be a less amount of type work.
  
    // Or
  
    obool var0 = ofalse ;
    obool var1 = otrue  ;   

**/

/** Why not reduce the size of ugly int sized _Bool ?
  * Normally because of internal compiler boolean integer computing.
  *
  * But you can use bool instead of obool !
**/

typedef uint_least8_t obool ;

#endif
