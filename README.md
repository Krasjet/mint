mint
====

mint is a C library to work music intervals. It contains a parser that converts
shorthand notation of music intervals [1] into an *invertible*, unambiguous
representation of music intervals, and several utility functions to work with
such representation, e.g. convert an interval into number of semitones.

The documentation of this library is in `mint.h`.

Grammar
-------

The BNF grammar for the shorthand notation is

    interval ::= quality number
    quality  ::= "P" | "M" | "m" | "A" | "AA" | "d" | "dd"
    number   ::= positive_int

where

    P  = perfect
    M  = major
    m  = minor
    A  = augmented
    AA = doubly augmented      <- yes, we support doubly augmented/diminished
    d  = diminished
    dd = doubly diminished

For example,

    mint_to_st(mint_from_str("M3")) == 4   /* major third */
    mint_to_st(mint_from_str("m3")) == 3   /* minor third */
    mint_to_st(mint_from_str("A3")) == 5   /* augmented third */
    mint_to_st(mint_from_str("d3")) == 2   /* diminished third */

This notation can be found in many music theory textbooks and references, but
they probably won't define it using the formal grammar above. It should be
generally understood by musicians, though.

Build
-----

mint does not depend on anything, even libc. Simply copy `mint.c` and `mint.h`
to your project and add

    #include "mint.h"

to any source file using the library.

You should be able to compile it with any C compiler compatible with C99.

[1]: https://en.wikipedia.org/wiki/Interval_(music)#Shorthand_notation
