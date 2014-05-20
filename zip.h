
#ifndef MACROFUN_ZIP_H
#define MACROFUN_ZIP_H


#include "args.h"       // ARGS_1ST, ARGS_2ND, ARGS_REST_TO_LIST
#include "blank.h"      // BLANK
#include "consume.h"    // CONSUME
#include "map-lists.h"  // MAP_LISTS
#include "separators.h" // SEP_COMMA
#include "stop-lists.h" // LISTS_APPEND_STOPS, IF_STOP_IN


// Takes `n` lists, and returns `m` lists of `n` elements, where `m` is
// the shortest length of all of the given lists.  The `i`th list of
// those `m` returned lists will consist of the `i`th elements in each
// of the `n` given lists.
//
// A list is a series of comma-separated expressions surrounded by
// parentheses, like `(1, 2, 3)`.
//
//      ZIP( (a) )                               >>>  (a)
//      ZIP( (a), (b), (c) )                     >>>  (a,b,c)
//      ZIP( (a,b), (c,d) )                      >>>  (a,c), (b,d)
//      ZIP( (a,b,c), (d,e,f), (g,h,i) )         >>>  (a,d,g), (b,e,h) (c,f,i)
//      ZIP( (a,b), () )                         >>>  (a,)
//      ZIP( (a,b), (c) )                        >>>  (a,c)
//      ZIP( (a), (b,c), (d) )                   >>>  (a,b,d)
//      ZIP( (a,b), (c,d,e), (f,g) )             >>>  (a,c,f), (b,d,g)
//      ZIP( (a,b), (c,d,e,f), (g,h,i), (j,k) )  >>>  (a,c,g,j), (b,d,h,k)
//
#define ZIP( ... ) \
    ZIP_EVAL( ZIP_0( LISTS_APPEND_STOPS( __VA_ARGS__ ) ) )


#define ZIP_0( ... ) \
    ( MAP_LISTS( ARGS_1ST, SEP_COMMA, __VA_ARGS__ ) ) \
    IF_STOP_IN( ( MAP_LISTS( ARGS_2ND, SEP_COMMA, __VA_ARGS__ ) ), \
                CONSUME, \
                ZIP_1 ) \
        BLANK ( MAP_LISTS( ARGS_REST_TO_LIST, SEP_COMMA, __VA_ARGS__ ) )

#define ZIP_1( ... ) \
    , ZIP_0 BLANK ( __VA_ARGS__ )


// Causes 256 rounds of evaluation of its arguments. This enables a crude
// form of recursion, with a maximum call-depth of 256. Each recursive macro
// needs to provide its own recursive evaluator, because a recursive
// evaluator can't be used recursively itself. This allows for recursive
// macros to be implemented with other recursive macros.
#define ZIP_EVAL( ... )     ZIP_EVAL255( __VA_ARGS__ )

#define ZIP_EVAL255( ... )  ZIP_EVAL127( ZIP_EVAL127( __VA_ARGS__ ) )
#define ZIP_EVAL127( ... )  ZIP_EVAL63( ZIP_EVAL63( __VA_ARGS__ ) )
#define ZIP_EVAL63( ... )   ZIP_EVAL31( ZIP_EVAL31( __VA_ARGS__ ) )
#define ZIP_EVAL31( ... )   ZIP_EVAL15( ZIP_EVAL15( __VA_ARGS__ ) )
#define ZIP_EVAL15( ... )   ZIP_EVAL7( ZIP_EVAL7( __VA_ARGS__ ) )
#define ZIP_EVAL7( ... )    ZIP_EVAL3( ZIP_EVAL3( __VA_ARGS__ ) )
#define ZIP_EVAL3( ... )    ZIP_EVAL1( ZIP_EVAL1( __VA_ARGS__ ) )
#define ZIP_EVAL1( ... )    __VA_ARGS__


#endif // ifndef MACROFUN_ZIP_H

