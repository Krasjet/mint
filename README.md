mint
====

mint is a C library to work music intervals, (tonal) pitches, and
transpositions.

It contains parsers that convert shorthand notation of music intervals [1] and
scientific pitch notation into *invertible*, unambiguous representations of
music intervals and tonal pitches.

mint also comes with several utility functions to work with these
representations, e.g. it can

- convert an interval into number of semitones
- convert a pitch into MIDI representation
- transpose a pitch in a way that distinguishes *enharmonically equivalent*
  notes, i.e. it treats notes like `C#` and `Db` differently.
- etc.

The documentation of this library is in `mint.h`, `pitch.h` and `transpose.h`.

Grammar: interval
-----------------

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

    mint_to_st(mint_parse("M3")) == 4   /* major third */
    mint_to_st(mint_parse("m3")) == 3   /* minor third */
    mint_to_st(mint_parse("A3")) == 5   /* augmented third */
    mint_to_st(mint_parse("d3")) == 2   /* diminished third */

This notation can be found in many music theory textbooks and references, but
they probably won't define it using the formal grammar above. It should be
generally understood by musicians, though.

Grammar: pitch
--------------

The BNF grammar for the scientific pitch notation is

    pitch       ::= pitch_class | pitch_class octave
    octave      ::= integer
    pitch_class ::= letter | letter accidental
    accidental  ::= sharp | flat | 'x'
    sharp       ::= '#' | '#' sharp
    flat        ::= 'b' | 'b' flat

where

    #  = sharp
    b  = flat
    x  = double sharp

Build
-----

mint consists of three component:

     +------+       +-------+
     | mint |       | pitch |
     +------+       +-------+
          ^           ^
          |           |
          +-----------+
          | transpose |
          +-----------+

`mint` and `pitch` are independent of each other, but `transpose` depends on
both `mint` and `pitch`.

This library does not have any external dependencies, even libc. Simply copy the corresponding `.c` and `.h` files to your project and add, for example

    #include "mint.h"

to any source file using this library.

You should be able to compile it with any C compiler compatible with C99.

trx
---

mint also comes with a simple demo called `trx` for transposing pitch classes.
Run

    $ make trx

to build it and then try the following in bash or zsh

    $ ./trx Ab <<< "A3 m13"
    C# Fb

[1]: https://en.wikipedia.org/wiki/Interval_(music)#Shorthand_notation
