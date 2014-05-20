
**[Macrofun](https://github.com/mcinglis/macrofun)** provides functional-programming macros for the C preprocessor, like mapping, folding and zipping over arguments in various forms.

 **Macrofun is just a demonstration; please don't use it.** It depends on preprocessing behavior of GCC and Clang that does not conform to the ISO C99 and C11 standard, even though it prompts no warnings for those preprocessors under `-std=c11 -Wall`. Section 6.10.3.4 paragraph 2 of the [C11 standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) specifies:

> If the name of the macro being replaced is found during this scan of the replacement list (not including the rest of the source file’s preprocessing tokens), it is not replaced. Furthermore, **if any nested replacements encounter the name of the macro being replaced, it is not replaced.** These nonreplaced macro name preprocessing tokens are no longer available for further replacement even if they are later (re)examined in contexts in which that macro name preprocessing token would otherwise have been replaced.

Therefore, it's a bug in GCC and Clang that they can be tricked into recursively expanding a macro under `-std=c99` and `-std=c11`, and Macrofun exploits that bug to the extreme.

``` c
#include <macrofun/foldl.h>         // FOLDL
#include <macrofun/intersperse.h>   // INTERSPERSE
#include <macrofun/map.h>           // MAP
#include <macrofun/map-lists.h>     // MAP_LISTS
#include <macrofun/separators.h>    // SEP_*
#include <macrofun/zip.h>           // ZIP
#include <macrofun/zip-repeat.h>    // ZIP_REPEAT

int main( void )
{
    #define PRINTD1( expr ) printf( "%s = %d\n", #expr, expr )
    #define PRINTD( ... ) MAP( PRINTD1, SEP_SEMICOLON, __VA_ARGS__ )
    PRINTD( 1 + 1,          // ==> 1 + 1 = 2
            8 / 2 * 3 );    // ==> 8 / 2 * 3 = 12
    MAP_LISTS( m, SEP_COMMA, (a,b), (c,d) )   // m(a, b), m(c, d)
    INTERSPERSE( SEP_AND, a, b, c, d )        // (a) && (b) && (c) && (d)
    FOLDL( m, acc, a, b, c )                  // m( m( m( acc, a ), b ), c )
    FOLDR( f, acc, a, b, c )                  // f( a, f( b, f( c, acc ) ) )
    // FOLDR breaks when folding with a macro expression, because the
    // preprocessor then detects and disables the recursion.
    ZIP( (a,b,c), (d,e,f,g), (h,i,j) )        // (a,d,h), (b,e,i), (c,f,j)
    ZIP_REPEAT( (a,b), (c,d), (e,f) )         // (a,b,c,d), (a,b,e,f)
}
```

The source files include extensive comments and example usage of each of the macros.

You can run the tests by executing `tests/run.bash`. These tests work by `diff`ing the output of `gcc -E` for each `.in.c` file against the corresponding `.out.c` file. These `out.c` files contain the specific whitespacing provided by GCC 4.8. Therefore, the tests may "fail" for other preprocessors, even though they output functionally equivalent code.

Macrofun has been tested with GCC 4.8 and Clang 3.4, on Fedora 20.

Macrofun's recursion method is derived from William Swanson's [map-macro](https://github.com/swansontec/map-macro).

It may seem like I've put a lot of effort into this. I have! I was going to release this as a fully-fledged library when I thought to actually check that recursive macros were allowed by the standard. I found out that they're explicitly prohibited. Moral of the story: don't rely on your compilers to check that your code conforms to the standards.

For what it's worth, I think it's regrettable that recursion is prohibited in the C preprocessor. I've played around with the possibilities provided by this library for a few months now, and I've seen it do a lot of good. Recursive macros give C programmers so much more power to manipulate their code. Things like `MAP` and `MAP_LISTS` can remove a lot of repetition in your code and your clients' code.

``` c
Test tests[] = {
    TEST( some_test_func ),
    TEST( another_test_func ),
    TEST( one_more_for_good_measure )
};
// could become:
Test tests[] = TESTS(
    some_test_func,
    another_test_func,
    one_more_for_good_measure
};

return assertions( ASSERTION( 23 > 12 ),
                   ASSERTION( "example"[ 2 ] == 'x' ),
                   ASSERTION( 8 * 2 == 16 ) );
// could become:
return assertions( 23 > 12,
                   "example"[ 2 ] == 'x',
                   8 * 2 == 16 );
```

``` c
#define ALL( ... ) INTERSPERSE( SEP_AND, __VA_ARGS__ )
#define ANY( ... ) INTERSPERSE( SEP_OR, __VA_ARGS__ )
#define ASSERT( ... ) MAP( assert, SEP_SEMICOLON, __VA_ARGS__ )

#define INVARIANTS_EMPTY( s ) \
    s.bytes == NULL, \
    s.length == 0, \
    s.capacity == 0

#define INVARIANTS_NONEMPTY( s ) \
    s.capacity > s.length, \
    s.bytes != NULL, \
    all_bytes_up_to_length_are_nonzero( s ), \
    s.bytes[ s.length ] == '\0', \

bool string_is_valid( String const s )
{
    return ALL( INVARIANTS_EMPTY( s ) )
        || ALL( INVARIANTS_NONEMPTY( s ) );
}

// We want fine-grained assertion errors, so we can't just do
// `assert( string_is_valid( s ) )`.
void string_assert_valid( String const s )
{
    if ( ANY( INVARIANTS_EMPTY( s ) ) ) {
        ASSERT( INVARIANTS_EMPTY( s ) );
    } else {
        ASSERT( INVARIANTS_NONEMPTY( s ) );
    }
}
```

`MAP_LISTS` makes it much easier to define generic functions for a set of types.

``` c
#define TYPE_SUFFIXES \
    ( bool, bools ), \
    ( char, chars ), \
    ( signed char, schars ), \
    ( unsigned char, uchars ), \
    ( short, shorts ), \
    /* 20 more lines snipped */

enum Ordering {
    Ordering_LT = -1,
    Ordering_EQ = 0,
    Ordering_GT = 1
};

#define COMPARE_PROTOTYPE( type, suffix ) \
    enum Ordering compare_##suffix( type, type );
MAP_LISTS( COMPARE_PROTOTYPE, SEP_NONE, COMPARABLE_TYPE_SUFFIXES )
// enum Ordering compare_bools( bool, bool );
// enum Ordering compare_chars( char, char );
// ...

#define COMPARE_IMPL( type, suffix ) \
    enum Ordering compare_##suffix( type const x, type const y ) \
    { \
        return ( x > y ) - ( x < y ); \
    }
MAP_LISTS( COMPARE_IMPL, SEP_NONE, COMPARABLE_TYPE_SUFFIXES )

#define COMPARE_TYPE_HANDLER( type, suffix ) \
    type:       compare_##suffix, \
    type const: compare_##suffix

#define compare( x, y ) \
    _Generic( x, \
        MAP_LISTS( COMPARE_TYPE_HANDLER, \
                   SEP_COMMA, \
                   COMPARABLE_TYPE_SUFFIXES ), \
        default: compare_pointers )( x, y )

// Likewise for `less_than`, `equal_to`, `greater_than`, etc. This might be
// useful if you want to provide comparison functions for the atomic types,
// so that others can map those function pointers over a data structure.
// Without `MAP_LISTS` (as per standards-conformant C), this is going to be
// a lot of repetition. The best approach would probably be to bring in a
// templating engine.
```

I'm on the fence as to if `FOLDL` is actually useful, or if the alternatives are always better:

``` c
#define MAX_TWO( x, y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )
#define MAX( n, ... ) FOLDL( MAX_TWO, n, __VA_ARGS__ )

#define PLUS( x, y ) ( ( x ) + ( y ) )
#define SUM( ... ) FOLDL( PLUS, 0, __VA_ARGS__ )
```

