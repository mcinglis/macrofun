
#ifndef MACROFUN_INTERSPERSE_H
#define MACROFUN_INTERSPERSE_H


#include "paren.h"  // PAREN
#include "map.h"    // MAP


// Takes a callable expression `sep`, and a variable number of following
// arguments, and returns those arguments parenthesesized, and separated by
// calls to `sep` with the previous argument.
//
//      INTERSPERSE( s, a )        >>>  ( a )
//      INTERSPERSE( s, a, b )     >>>  ( a ) s( a ) ( b )
//      INTERSPERSE( s, a, b, c )  >>>  ( a ) s( a ) ( b ) s( b ) ( c )
//
// `separators.h` provides macros that evaluate to a constant expression. For
// example, `INTERSPERSE( SEP_AND, ... )` will separate each variable
// argument by `&&`.
#define INTERSPERSE( sep, ... ) \
    MAP( PAREN, sep, __VA_ARGS__ )


#endif // ifndef MACROFUN_INTERSPERSE_H

