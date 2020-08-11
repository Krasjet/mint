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
 * An invertible representation of music intervals optimized for computation.
 *
 * A music interval should have a non-negative, 0-indexed interval size, i.e.
 * unison = 0, third = 2, etc., and a quality offset, which is the number of
 * semitones deviate from perfect or major (i.e. major scale).
 *
 * For example, minor third should have
 *  - size: 2
 *  - qoffset: -1
 * and augmented fifth should have
 *  - size: 4
 *  - qoffset: 1
 *
 * The quality of the interval itself is not encoded in the representation, use
 * mint_get_quality to get the quality of an interval.
 *
 * By convention, we always count from lower pitch to higher pitch, so any
 * interval with negative size is invalid. You should error check against this.
 */
struct mint {
  int size; /* < 0 is invalid interval */
  int qoffset;
};

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
 * If parsing error occurs, the size of the returned mint is set to be
 * negative.
 */
struct mint mint_parse(const char *s);

/*
 * Get the quality of a music interval, which is one of
 *
 *    dd d m M P A AA
 *
 * This function does no error checking. Make sure you check for parsing error
 * before passing the result to this function.
 *
 * Contracts:
 *   - interval.size >= 0
 *   - -2 <= interval.qoffset <= 2 for perfectable intervals (unison, 4th, 5th, octave, etc)
 *   - -3 <= interval.qoffset <= 2 otherwise
 */
enum mint_quality mint_get_quality(struct mint interval);


/*
 * Get the offset of interval quality in semitones.
 *
 * Note that interval size is also needed to determine the size. It is roughly
 * the inverse of mint_get_quality.
 *
 * This function does no error checking.
 *
 * Contracts:
 *   - size >= 0
 */
int mint_qoffset(enum mint_quality qual, int size);

/*
 * Convert music interval to semitones (st).
 *
 * The conversion is not injective and thus not invertible.
 *
 * This function does no error checking. Make sure you check for parsing error
 * before passing the result to this function.
 *
 * Contracts:
 *   - interval.size >= 0
 */
int mint_to_st(struct mint interval);

#endif
