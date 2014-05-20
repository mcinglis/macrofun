
#ifndef MACROFUN_CALL_H
#define MACROFUN_CALL_H


// Lazily calls the given macro with the given variable arguments, so
// that its arguments are parsed as the list they evaluated to, rather
// than the list they were coded as.
#define CALL( m, ... ) m( __VA_ARGS__ )


#endif // ifndef MACROFUN_CALL_H

