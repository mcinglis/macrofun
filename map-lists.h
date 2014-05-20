
#ifndef MACROFUN_MAP_LISTS_H
#define MACROFUN_MAP_LISTS_H


#include "blank.h"      // BLANK
#include "consume.h"    // CONSUME
#include "stop.h"       // IF_STOP, STOP


// Takes two callable expressions `m` and `sep` and a variable number of
// lists, and consecutively calls `m` with the elements of each list.  Each
// `m( ... )` call will be separated by `sep( ... )`, where the arguments to
// `sep` are the elements of the next list that `m` will be called with.
//
//      MAP_LISTS( m, s, (a) )
//      >>>  m( a )
//      MAP_LISTS( m, s, (a,b), (c) )
//      >>>  m( a, b ) s( c ) m( c )
//      MAP_LISTS( m, s, (a,b,c), (d), (e,f) )
//      >>>  m( a, b, c ) s( d ) m( d ) s( e, f ) m( e, f )
//
// `separators.h` provides macros that evaluate to a constant expression. For
// example, `MAP_LISTS( m, SEP_AND, ... )` will separate each resulting `m`
// call by `&&`.
#define MAP_LISTS( m, sep, ... ) \
    MAP_LISTS_EVAL( MAP_LISTS_0( m, sep, __VA_ARGS__, STOP, 0 ) )

#define MAP_LISTS_0( m, sep, head, next, ... ) \
    m head \
    IF_STOP( next, CONSUME, MAP_LISTS_1 ) \
        BLANK ( m, sep, next, __VA_ARGS__ )

#define MAP_LISTS_1( m, sep, next, ... ) \
    sep next  MAP_LISTS_0 BLANK ( m, sep, next, __VA_ARGS__ )


// Causes 256 rounds of evaluation of its arguments. This enables a crude
// form of recursion, with a maximum call-depth of 256. Each recursive macro
// needs to provide its own recursive evaluator, because a recursive
// evaluator can't be used recursively itself. This allows for recursive
// macros to be implemented with other recursive macros.
#define MAP_LISTS_EVAL( ... ) \
    MAP_LISTS_EVAL255( __VA_ARGS__ )

#define MAP_LISTS_EVAL255( ... ) \
    MAP_LISTS_EVAL127( MAP_LISTS_EVAL127( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL127( ... ) \
    MAP_LISTS_EVAL63( MAP_LISTS_EVAL63( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL63( ... ) \
    MAP_LISTS_EVAL31( MAP_LISTS_EVAL31( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL31( ... ) \
    MAP_LISTS_EVAL15( MAP_LISTS_EVAL15( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL15( ... ) \
    MAP_LISTS_EVAL7( MAP_LISTS_EVAL7( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL7( ... ) \
    MAP_LISTS_EVAL3( MAP_LISTS_EVAL3( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL3( ... ) \
    MAP_LISTS_EVAL1( MAP_LISTS_EVAL1( __VA_ARGS__ ) )
#define MAP_LISTS_EVAL1( ... ) \
    __VA_ARGS__


#endif // ifndef MACROFUN_MAP_LISTS_H

