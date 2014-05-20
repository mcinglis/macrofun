
#ifndef MACROFUN_MAP_H
#define MACROFUN_MAP_H


#include "blank.h"      // BLANK
#include "consume.h"    // CONSUME
#include "stop.h"       // IF_STOP, STOP


// Takes two callable expressions `m` and `sep`, and calls `m` with each
// consecutive variable argument, separating each `m( x )` call by
// `sep( y )`, where `y` is the next variable argument after `x`.
//
//      MAP( m, s, x )        >>>  m( x )
//      MAP( m, s, x, y )     >>>  m( x ) s( y ) m( y )
//      MAP( m, s, x, y, z )  >>>  m( x ) s( y ) m( y ) s( z ) m( z )
//
// `separators.h` provides macros that evaluate to a constant expression. For
// example, `MAP( m, SEP_AND, ... )` will separate each resulting `m` call by
// `&&`.
#define MAP( m, sep, ... ) \
    MAP_EVAL( MAP_0( m, sep, __VA_ARGS__, STOP, 0 ) )

#define MAP_0( m, sep, head, next, ... ) \
    m( head ) \
    IF_STOP( next, CONSUME, MAP_1 ) \
        BLANK ( m, sep, next, __VA_ARGS__ )

#define MAP_1( m, sep, next, ... ) \
    sep( next ) MAP_0 BLANK ( m, sep, next, __VA_ARGS__ )


// Causes 256 rounds of evaluation of its arguments. This enables a crude
// form of recursion, with a maximum call-depth of 256. Each recursive macro
// needs to provide its own recursive evaluator, because a recursive
// evaluator can't be used recursively itself. This allows for recursive
// macros to be implemented with other recursive macros.
#define MAP_EVAL( ... )    MAP_EVAL255( __VA_ARGS__ )

#define MAP_EVAL255( ... ) MAP_EVAL127( MAP_EVAL127( __VA_ARGS__ ) )
#define MAP_EVAL127( ... ) MAP_EVAL63( MAP_EVAL63( __VA_ARGS__ ) )
#define MAP_EVAL63( ... )  MAP_EVAL31( MAP_EVAL31( __VA_ARGS__ ) )
#define MAP_EVAL31( ... )  MAP_EVAL15( MAP_EVAL15( __VA_ARGS__ ) )
#define MAP_EVAL15( ... )  MAP_EVAL7( MAP_EVAL7( __VA_ARGS__ ) )
#define MAP_EVAL7( ... )   MAP_EVAL3( MAP_EVAL3( __VA_ARGS__ ) )
#define MAP_EVAL3( ... )   MAP_EVAL1( MAP_EVAL1( __VA_ARGS__ ) )
#define MAP_EVAL1( ... )   __VA_ARGS__


#endif // ifndef MACROFUN_MAP_H

