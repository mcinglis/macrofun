
#ifndef MACROFUN_STOP_LISTS_H
#define MACROFUN_STOP_LISTS_H


#include "foldl.h"      // FOLDL
#include "map-lists.h"  // MAP_LISTS
#include "paren.h"      // UNPAREN
#include "stop.h"       // STOP, IF_STOP, IF_STOP_STOP


#define LISTS_APPEND_STOPS( ... ) \
    MAP_LISTS( ARGS_TO_STOPPED_LIST, SEP_COMMA, __VA_ARGS__ )

// Gives a list containing the given arguments and two `STOP`s. The two
// `STOP`s allow macros working with the list to determine the stopping
// point while avoiding missing argument warnings or errors.
#define ARGS_TO_STOPPED_LIST( ... ) \
    ( __VA_ARGS__, STOP, STOP )


// If the given list contains `STOP`, this evaluates to the given `then`.
// Otherwise, this evaluates to the given `els`.
#define IF_STOP_IN( list, then, els ) \
    IF_STOP( FOLDL( IF_STOP_STOP, 0, UNPAREN( list ) ), then, els )


#endif // ifndef MACROFUN_STOP_LISTS_H

