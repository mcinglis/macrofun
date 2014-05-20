
#ifndef MACROFUN_BLANK_H
#define MACROFUN_BLANK_H


// Preprocessor recursion can occur between two different macros; a macro
// can't recurse directly into itself, but it can call another macro that
// calls the first again. This value should be used to separate the name of
// the paired macro, and its argument list; see `map.h` as an example.
#define BLANK


#endif // ifndef MACROFUN_BLANK_H

