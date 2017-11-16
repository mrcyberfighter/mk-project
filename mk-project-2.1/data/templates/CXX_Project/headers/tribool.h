#ifndef TRIBOOLEAN_LOGIC_HH
#define TRIBOOLEAN_LOGIC_HH

#ifdef TRIBOOL                 /**  The idea is to make a trilogic boolean type. **/
#include <cstdint>

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

       I've learn in this time about the existents into libboost of the triboolean type.
        

struct tbool {

  const uint_least8_t const tb_minus  : 2 ;
  const uint_least8_t const tb_none   : 1 ;
  const uint_least8_t const tb_plus   : 1 ;

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

#endif
