#ifndef MINT_H
#define MINT_H

/*
 * Quality of a music interval. We do allow doubly augmented/diminished.
 */
enum mint_quality {
  MINT_DOUBLY_DIMINISHED = 0,
  MINT_DIMINISHED,
  MINT_MINOR,
  MINT_MAJOR,
  MINT_PERFECT,
  MINT_AUGMENTED,
  MINT_DOUBLY_AUGMENTED
};

/*
 * An invertible representation of music intervals.
 *
 * mint_t should have a quality, which is one of
 *
 *    dd d m M P A AA
 *
 * and a non-negative, 0-indexed interval size, i.e. unison = 0, third = 2,
 * etc. This makes transposition much easier.
 *
 * By convention, we always count from lower pitch to higher pitch, so any
 * interval with negative size is invalid.
 */
typedef struct {
  enum mint_quality quality;
  int size; /* < 0 is invalid interval */
} mint_t;

/*
 * Parse music intervals from string (shorthand notations).
 *
 * Some examples of the the shorthand notation:
 *   - M3 = major third      = 4 semitones
 *   - m3 = minor third      = 3 semitones
 *   - A3 = augmented third  = 5 semitones
 *   - d3 = diminished third = 2 semitones
 * See the README for a formal grammar definition of the notation.
 *
 * We don't accept negative interval size, but just to keep things simple, we
 * do allow things like doubly diminished unison (`dd1`), which is -2 semitones.
 *
 * If parsing error occurs, the size of the returned mint_t is set to be
 * negative.
 */
mint_t mint_from_str(const char *s);

/*
 * Get the offset of interval quality in semitones.
 *
 * Note that interval size is also needed to determine the size.
 *
 * This function does no error checking.
 */
int mint_qualoffset(enum mint_quality qual, int size);

/*
 * Convert music interval to semitones (st).
 *
 * This function is not injective and thus not invertible.
 *
 * This function does no error checking. If you are using the result from
 * mint_from_str, make sure to check for parsing error before passing the
 * result to this function.
 */
int mint_to_st(mint_t interval);

#endif
