
#ifndef MACROFUN_FOLDL_H
#define MACROFUN_FOLDL_H


#include "args.h"       // ARGS_2ND
#include "blank.h"      // BLANK
#include "consume.h"    // CONSUME
#include "paren.h"      // UNPAREN
#include "stop.h"       // STOP2, IF_STOP2


// Given an expression callable with two arguments, a starting value, and a
// variable number of expressions, this returns a reduction of those
// expressions using the given callable, from left to right.
//
//      FOLDL( m, acc, a )        >>>  m( acc, a )
//      FOLDL( m, acc, a, b )     >>>  m( m( acc, a ), b )
//      FOLDL( m, acc, a, b, c )  >>>  m( m( m( acc, a ), b ), c )
//
#define FOLDL( m, acc, ... ) \
    FOLDL_EVAL( FOLDL_0( m, acc, __VA_ARGS__, STOP2, 0 ) )

#define FOLDL_0( m, acc, head, next, ... ) \
    IF_STOP2( next, ARGS_2ND, FOLDL_1 ) \
        BLANK ( m, m( acc, head ), next, __VA_ARGS__ )

#define FOLDL_1( ... ) \
    FOLDL_0 BLANK ( __VA_ARGS__ )

// Note that we use `STOP2` and `IF_STOP2`, so that we can accept `STOP` as a
// valid argument to fold over; this feature is used to implement
// `IF_STOP_IN`.


// Causes 256 rounds of evaluation of its arguments. This enables a crude
// form of recursion, with a maximum call-depth of 256. Each recursive macro
// needs to provide its own recursive evaluator, because a recursive
// evaluator can't be used recursively itself. This allows for recursive
// macros to be defined in terms of other recursive macros.
#define FOLDL_EVAL( ... )     FOLDL_EVAL255( __VA_ARGS__ )

#define FOLDL_EVAL255( ... )  FOLDL_EVAL127( FOLDL_EVAL127( __VA_ARGS__ ) )
#define FOLDL_EVAL127( ... )  FOLDL_EVAL63( FOLDL_EVAL63( __VA_ARGS__ ) )
#define FOLDL_EVAL63( ... )   FOLDL_EVAL31( FOLDL_EVAL31( __VA_ARGS__ ) )
#define FOLDL_EVAL31( ... )   FOLDL_EVAL15( FOLDL_EVAL15( __VA_ARGS__ ) )
#define FOLDL_EVAL15( ... )   FOLDL_EVAL7( FOLDL_EVAL7( __VA_ARGS__ ) )
#define FOLDL_EVAL7( ... )    FOLDL_EVAL3( FOLDL_EVAL3( __VA_ARGS__ ) )
#define FOLDL_EVAL3( ... )    FOLDL_EVAL1( FOLDL_EVAL1( __VA_ARGS__ ) )
#define FOLDL_EVAL1( ... )    __VA_ARGS__


#endif // ifndef MACROFUN_FOLDL_H

