
#ifndef MACROFUN_LIST_H
#define MACROFUN_LIST_H


#include "blank.h"  // BLANK
#include "paren.h"  // UNPAREN


// Returns a new list containing all but the first element of the given list
// `xs`.
//
//      LIST_REST( () )           >>>  ()
//      LIST_REST( ( a ) )        >>>  ()
//      LIST_REST( ( a, b ) )     >>>  ( b )
//      LIST_REST( ( a, b, c ) )  >>>  ( b, c )
//
#define LIST_REST( xs ) \
    LIST_REST_ BLANK ( UNPAREN( xs ) )
#define LIST_REST_( x, ... ) ( __VA_ARGS__ )


// Returns the first element of the given list `XS`.
//
//      LIST_1ST( () )            >>>
//      LIST_1ST( ( a ) )         >>>  a
//      LIST_1ST( ( a, b ) )      >>>  a
//      LIST_1ST( ( ( a ), b ) )  >>>  ( a )
//
#define LIST_1ST( xs ) \
    LIST_1ST_ BLANK ( UNPAREN( xs ) )
#define LIST_1ST_( x, ... ) x


// Returns the second element of the given list.
//
//      LIST_2ND( () )           >>>
//      LIST_2ND( ( a ) )        >>>
//      LIST_2ND( ( a, b ) )     >>>  b
//      LIST_2ND( ( a, b, c ) )  >>>  b
//      LIST_2ND( ( a, ( b ) )   >>>  ( b )
//
#define LIST_2ND( xs ) \
    LIST_2ND_ BLANK ( UNPAREN( xs ) )
#define LIST_2ND_( x, y, ... ) y


#endif // ifndef MACROFUN_LIST_H

