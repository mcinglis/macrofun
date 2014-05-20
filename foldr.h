
#ifndef MACROFUN_FOLDR_H
#define MACROFUN_FOLDR_H


#include "args.h"       // ARGS_2ND
#include "blank.h"      // BLANK
#include "consume.h"    // CONSUME
#include "paren.h"      // UNPAREN
#include "stop.h"       // STOP2, IF_STOP2


// Given a non-macro expression callable with two arguments, a starting
// value, and a variable number of expressions, this returns a reduction of
// those expressions using the given callable, from left to right.
//
//      FOLDR( f, acc, a )        >>>  f( a, acc )
//      FOLDR( f, acc, a, b )     >>>  f( a, f( b, acc ) )
//      FOLDR( f, acc, a, b, c )  >>>  f( a, f( b, f( c, acc ) ) )
//
// Note that this breaks when given a macro, because GCC and Clang then
// detect and disable the recursion.
#define FOLDR( f, acc, ... ) \
    FOLDR_EVAL( FOLDR_0( f, acc, __VA_ARGS__, STOP2, 0 ) )

#define FOLDR_0( f, acc, head, next, ... ) \
    f( head, \
       IF_STOP2( next, acc CONSUME, FOLDR_1 ) \
           BLANK ( f, acc, next, __VA_ARGS__ ) )

#define FOLDR_1( ... ) \
    FOLDR_0 BLANK ( __VA_ARGS__ )

// Note that we use `STOP2` and `IF_STOP2`, so that we can accept `STOP` as a
// valid argument to fold over; this feature is used to implement
// `IF_STOP_IN`.


// Causes 256 rounds of evaluation of its arguments. This enables a crude
// form of recursion, with a maximum call-depth of 256. Each recursive macro
// needs to provide its own recursive evaluator, because a recursive
// evaluator can't be used recursively itself. This allows for recursive
// macros to be defined in terms of other recursive macros.
#define FOLDR_EVAL( ... )     FOLDR_EVAL255( __VA_ARGS__ )

#define FOLDR_EVAL255( ... )  FOLDR_EVAL127( FOLDR_EVAL127( __VA_ARGS__ ) )
#define FOLDR_EVAL127( ... )  FOLDR_EVAL63( FOLDR_EVAL63( __VA_ARGS__ ) )
#define FOLDR_EVAL63( ... )   FOLDR_EVAL31( FOLDR_EVAL31( __VA_ARGS__ ) )
#define FOLDR_EVAL31( ... )   FOLDR_EVAL15( FOLDR_EVAL15( __VA_ARGS__ ) )
#define FOLDR_EVAL15( ... )   FOLDR_EVAL7( FOLDR_EVAL7( __VA_ARGS__ ) )
#define FOLDR_EVAL7( ... )    FOLDR_EVAL3( FOLDR_EVAL3( __VA_ARGS__ ) )
#define FOLDR_EVAL3( ... )    FOLDR_EVAL1( FOLDR_EVAL1( __VA_ARGS__ ) )
#define FOLDR_EVAL1( ... )    __VA_ARGS__


#endif // ifndef MACROFUN_FOLDR_H

