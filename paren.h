
#ifndef MACROFUN_PAREN_H
#define MACROFUN_PAREN_H


// Surrounds the given arguments with parentheses.
#define PAREN( ... ) \
    ( __VA_ARGS__ )


// Strips the given argument of its outer-most parentheses.
#define UNPAREN( x ) \
    UNPAREN_ x
#define UNPAREN_( ... ) __VA_ARGS__


#endif // ifndef MACROFUN_PAREN_H

