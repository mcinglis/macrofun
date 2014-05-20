
#ifndef MACROFUN_SEPARATORS_H
#define MACROFUN_SEPARATORS_H


// You can pass one of these following separator macros as the separator
// argument to `MAP`, `MAP_LISTS` or `INTERSPERSE` to separate each resulting
// expression by a constant expression. Separators have to be provided in
// this format because the simpler approach (i.e. `MAP( m, +, ... )`) won't
// work for commas, and I was keen to provide a uniform interface. Also, that
// approach wouldn't be as flexible or powerful.
//
//      MAP( m, SEP_NONE, a, b, c )           >>>  m( a ) m( b ) m( c )
//      MAP( m, SEP_COMMA, a, b, c )          >>>  m( a ), m( b ), m( c )
//      MAP( m, SEP_AND, a, b, c )            >>>  m( a ) && m( b ) && m( c )
//      MAP_LISTS( m, SEP_NONE, (a,b), (c) )  >>>  m( a, b ) m( c )
//      MAP_LISTS( m, SEP_OR, (a,b), (c) )    >>>  m( a, b ) || m( c )
//      INTERSPERSE( SEP_AND, a, b, c )       >>>  ( a ) && ( b ) && ( c )
//
// Be careful about how you use some of these separators. For example, the
// comparison operators don't work like mathematical notation when they're
// chained: `2 < 3 < 2 == true`.

#define SEP_NONE( ... )
#define SEP_COMMA( ... )                ,
#define SEP_SEMICOLON( ... )            ;
#define SEP_PLUS( ... )                 +
#define SEP_MINUS( ... )                -
#define SEP_TIMES( ... )                *
#define SEP_DIVIDE( ... )               /
#define SEP_MODULO( ... )               %
#define SEP_AND( ... )                  &&
#define SEP_OR( ... )                   ||
#define SEP_LT( ... )                   <
#define SEP_LE( ... )                   <=
#define SEP_EQ( ... )                   ==
#define SEP_NEQ( ... )                  !=
#define SEP_GE( ... )                   >=
#define SEP_GT( ... )                   >
#define SEP_BIT_AND( ... )              &
#define SEP_BIT_OR( ... )               |
#define SEP_BIT_XOR( ... )              ^
#define SEP_BIT_LSHIFT( ... )           <<
#define SEP_BIT_RSHIFT( ... )           >>
#define SEP_ASSIGN( ... )               =
#define SEP_PLUS_ASSIGN( ... )          +=
#define SEP_MINUS_ASSIGN( ... )         -=
#define SEP_TIMES_ASSIGN( ... )         *=
#define SEP_DIVIDE_ASSIGN( ... )        /=
#define SEP_MODULO_ASSIGN( ... )        %=
#define SEP_BIT_AND_ASSIGN( ... )       &=
#define SEP_BIT_OR_ASSIGN( ... )        |=
#define SEP_BIT_XOR_ASSIGN( ... )       ^=
#define SEP_BIT_LSHIFT_ASSIGN( ... )    <<=
#define SEP_BIT_RSHIFT_ASSIGN( ... )    >>=
#define SEP_FIELD( ... )                .
#define SEP_DEREF_FIELD( ... )          ->


#endif // ifndef MACROFUN_SEPARATORS_H

