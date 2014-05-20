
#ifndef MACROFUN_ARGS_H
#define MACROFUN_ARGS_H


#define ARGS_1ST( x, ... ) x
#define ARGS_2ND( x, y, ... ) y
#define ARGS_REST( x, ... ) __VA_ARGS__
#define ARGS_REST_TO_LIST( ... ) ( ARGS_REST( __VA_ARGS__ ) )


#endif // ifndef MACROFUN_ARGS_H

