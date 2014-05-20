
#ifndef MACROFUN_STOP_H
#define MACROFUN_STOP_H


#include "args.h"   // ARGS_2ND
#include "call.h"   // CALL
#include "list.h"   // LIST_2ND


// The end-sentinel of a series of comma-separated expressions.
#define STOP ((((((()))))))


// If `x` is `STOP` (or, really, just begins with as many parentheses as
// `STOP` does), this evaluates to the given `then`.  Otherwise, this
// evaluates to the given `els` (else).
#define IF_STOP( x, then, els ) \
    CALL( ARGS_2ND, COMMA_IF_STOP( x ) then, els, 0 )


// If `x` is `STOP` (or, really, just begins with as many parentheses as
// `STOP` does), this evaluates to `STOP`.  Otherwise, this evaluates to
// the given `els`. This can be used with `FOLDL` to reduce a series of
// expressions to `STOP` if any expression was `STOP`.
#define IF_STOP_STOP( x, els ) \
    IF_STOP( x, STOP, els )


// If the given expression is `STOP` (or, really, just begins with as many
// parentheses as `STOP` does), this evaluates to `,`.  Otherwise, this
// evaluates to some expression without a comma. This can be used to shuffle
// the positions of arguments.
#define COMMA_IF_STOP( ... ) \
    COMMA_IF_STOP_7_0( __VA_ARGS__ )

#define COMMA_IF_STOP_7_0( ... ) COMMA_IF_STOP_7_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_7_1( x7, ... ) COMMA_IF_STOP_6_0 x7
#define COMMA_IF_STOP_6_0( ... ) COMMA_IF_STOP_6_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_6_1( x7, ... ) COMMA_IF_STOP_5_0 x7
#define COMMA_IF_STOP_5_0( ... ) COMMA_IF_STOP_5_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_5_1( x7, ... ) COMMA_IF_STOP_4_0 x7
#define COMMA_IF_STOP_4_0( ... ) COMMA_IF_STOP_4_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_4_1( x7, ... ) COMMA_IF_STOP_3_0 x7
#define COMMA_IF_STOP_3_0( ... ) COMMA_IF_STOP_3_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_3_1( x7, ... ) COMMA_IF_STOP_2_0 x7
#define COMMA_IF_STOP_2_0( ... ) COMMA_IF_STOP_2_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_2_1( x7, ... ) COMMA_IF_STOP_1_0 x7
#define COMMA_IF_STOP_1_0( ... ) COMMA_IF_STOP_1_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_1_1( x7, ... ) COMMA_IF_STOP_0_0 x7
#define COMMA_IF_STOP_0_0( ... ) COMMA_IF_STOP_0_1( __VA_ARGS__, 0 )
#define COMMA_IF_STOP_0_1( x7, ... ) x7,

// Each `_0` macro appends a `0` to the call to the associated `_1` macro, to
// occupy the var-args argument when it would have otherwise been called with
// a single token (this is required for strict ISO standards conformance).
// The `_1` macros will call the following `_0` if their first argument
// begins with parentheses, thereby stripping one layer of parentheses.



// You can use this as the end-sentinel instead, if you want to accept
// `STOP` as a valid argument.
#define STOP2 (STOP)


// If the given expression is `STOP2` (or, really, just begins with as many
// parentheses as `STOP2` does), this evaluates to `,`.  Otherwise, this
// evaluates to some expression without a comma. This can be used to shuffle
// the positions of arguments.
#define COMMA_IF_STOP2( x ) COMMA_IF_STOP x


// If `x` is `STOP2` (or, really, just begins with as many parentheses as
// `STOP2` does), this evaluates to the given `then`.  Otherwise, this
// evaluates to the given `els`.
#define IF_STOP2( x, then, els ) \
    LIST_2ND( ( COMMA_IF_STOP2( x ) then, els, 0 ) )


#endif // ifndef MACROFUN_STOP_H

