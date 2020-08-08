mint
====

This library contains a parser for converting a music interval in shorthand
notations into semitones.

The BNF grammar for the notation is

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

    parse_interval("M3") == 4   /* major third */
    parse_interval("m3") == 3   /* minor third */
    parse_interval("A3") == 5   /* augmented third */
    parse_interval("d3") == 2   /* diminished third */

This notation can be found in many music theory textbooks and references,
but they probably won't define it using the formal grammar above. This
notation should be generally understood by musicians, though.

We don't accept negative interval number, but just to keep things simple, we do
allow interval size to be negative, e.g. doubly diminished unison (`dd1`) is -2
semitones. Therefore, you should check for error by comparing against
`MINT_MIN`, which is the minimum of semitone values, namely -2 for `dd1`.

For example,

    if (parse_interval("P3") < MINT_MIN) {
      error("there is no perfect third!!!");
    }
