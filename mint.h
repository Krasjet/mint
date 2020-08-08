#ifndef MINT_H
#define MINT_H

/*
 * The smallest possible interval value, anything
 * below this value is an error.
 */
#define MINT_MIN (-2)

/*
 * Convert a music interval string (in shorthand notations) into semitones.
 *
 * Some examples of the the shorthand notation:
 *   - M3 = major third      = 4 semitones
 *   - m3 = minor third      = 3 semitones
 *   - A3 = augmented third  = 5 semitones
 *   - d3 = diminished third = 2 semitones
 * See the README for a formal grammar definition of the notation.
 *
 * We don't accept negative interval number, but just to keep things simple, we
 * do allow interval size to be negative, e.g. doubly diminished unison (`dd1`)
 * is -2 semitones. Therefore, you should check for error by comparing against
 * `MINT_MIN`. The return value would be error if it is less than `MINT_MIN`.
 */
int mint_parse(const char* s);

#endif
