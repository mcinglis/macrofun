
#ifndef MACROFUN_ZIP_REPEAT_H
#define MACROFUN_ZIP_REPEAT_H


#include "args.h"       // ARGS_1ST, ARGS_2ND, ARGS_REST_TO_LIST
#include "blank.h"      // BLANK
#include "consume.h"    // CONSUME
#include "map-lists.h"  // MAP_LISTS
#include "paren.h"      // UNPAREN
#include "separators.h" // SEP_COMMA
#include "stop-lists.h" // LISTS_APPEND_STOPS, IF_STOP_IN


// Takes a list containing `x` elements, and `n` following lists, and
// returns `m` lists of `x + n` elements, where `m` is the shortest
// length of all of the `n` lists.  The `i`th list of those `m` returned
// lists will consist of the `x` elements from the first given list, and
// the `i`th elements in each of the `n` given lists.
//
// A list is a series of comma-separated expressions surrounded by
// parentheses, like `(1, 2, 3)`.
//
//      ZIP_REPEAT( (), (a), (b) )                >>>  (,a,b)
//      ZIP_REPEAT( (a), (b,c), (d,e) )           >>>  (a,b,d), (a,c,e)
//      ZIP_REPEAT( (a), (b), (c,d) )             >>>  (a,b,c)
//      ZIP_REPEAT( (a,b), (), () )               >>>  (a,b,,)
//      ZIP_REPEAT( (a,b), (c,d), (e,f) )         >>>  (a,b,c,e), (a,b,d,f)
//      ZIP_REPEAT( (a,b), (c), (d,e) )           >>>  (a,b,c,d)
//      ZIP_REPEAT( (a), (b), (c,d,e), (f,g) )    >>>  (a,b,c,f)
//      ZIP_REPEAT( (a,b), (c), (d,e,f), (g,h) )  >>>  (a,b,c,d,g)
//      ZIP_REPEAT( (a), (b,c), (d,e,f), (g,h) )  >>>  (a,b,d,g), (a,c,e,h)
//      ZIP_REPEAT( (a,b), (c,d), (e,f,g), (h,i) )
//      >>>  (a,b,c,e,h), (a,b,d,f,i)
//
#define ZIP_REPEAT( xs, ... ) \
    ZIP_REPEAT_EVAL( ZIP_REPEAT_0( xs, LISTS_APPEND_STOPS( __VA_ARGS__ ) ) )

#define ZIP_REPEAT_0( xs, ... ) \
    ( UNPAREN( xs ), MAP_LISTS( ARGS_1ST, SEP_COMMA, __VA_ARGS__ ) ) \
    IF_STOP_IN( ( MAP_LISTS( ARGS_2ND, SEP_COMMA, __VA_ARGS__ ) ), \
                CONSUME, \
                ZIP_REPEAT_1 ) \
        BLANK ( xs, MAP_LISTS( ARGS_REST_TO_LIST, SEP_COMMA, __VA_ARGS__ ) )

#define ZIP_REPEAT_1( ... ) \
    , ZIP_REPEAT_0 BLANK ( __VA_ARGS__ )


// Causes 256 rounds of evaluation of its arguments. This enables a crude
// form of recursion, with a maximum call-depth of 256. Each recursive macro
// needs to provide its own recursive evaluator, because a recursive
// evaluator can't be used recursively itself. This allows for recursive
// macros to be implemented with other recursive macros.
#define ZIP_REPEAT_EVAL( ... ) \
    ZIP_REPEAT_EVAL255( __VA_ARGS__ )

#define ZIP_REPEAT_EVAL255( ... ) \
    ZIP_REPEAT_EVAL127( ZIP_REPEAT_EVAL127( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL127( ... ) \
    ZIP_REPEAT_EVAL63( ZIP_REPEAT_EVAL63( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL63( ... ) \
    ZIP_REPEAT_EVAL31( ZIP_REPEAT_EVAL31( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL31( ... ) \
    ZIP_REPEAT_EVAL15( ZIP_REPEAT_EVAL15( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL15( ... ) \
    ZIP_REPEAT_EVAL7( ZIP_REPEAT_EVAL7( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL7( ... ) \
    ZIP_REPEAT_EVAL3( ZIP_REPEAT_EVAL3( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL3( ... ) \
    ZIP_REPEAT_EVAL1( ZIP_REPEAT_EVAL1( __VA_ARGS__ ) )
#define ZIP_REPEAT_EVAL1( ... ) \
    __VA_ARGS__


#endif // ifndef MACROFUN_ZIP_REPEAT_H

