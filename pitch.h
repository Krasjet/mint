#ifndef PITCH_H
#define PITCH_H

/* The letter, i.e. step of a pitch class */
enum pitch_letter {
  PITCH_C = 0,
  PITCH_D,
  PITCH_E,
  PITCH_F,
  PITCH_G,
  PITCH_A,
  PITCH_B,
};

/* Convert letter to corresponding char */
char pitch_letter_to_char(enum pitch_letter l);
/*
 * Inverse of pitch_letter_to_char
 *
 * Contracts:
 *   - 'A' <= ch <= 'G'
 */
enum pitch_letter pitch_char_to_letter(char ch);

/*
 * Constants only for accessing accidentals in programs. This list is not
 * exhaustive
 */
enum {
  PITCH_DOUBLE_FLAT = -2,
  PITCH_FLAT = -1,
  PITCH_NATURAL = 0,
  PITCH_SHARP = 1,
  PITCH_DOUBLE_SHARP = 2,
};

/* An invertible representation of (tonal) pitch classes. */
struct pitch_class {
  enum pitch_letter letter;
  int accidental; /* because of transposition, we can get at most #### and bbbb */
};

/* Convert pitch class to index, where C = 0 and B = 11 */
int pitch_pc_to_idx(struct pitch_class pc);
/*
 * Convert pitch class to ascii notation, e.g. C#, Cx, Cb.
 *
 * Contracts:
 *   - out has buffer size at least abs(pc.accidental) + 2
 */
void pitch_pc_to_ascii(struct pitch_class pc, char *out);

/*
 * Parse pitch class from s.
 *
 * The returned points after the last valid token. For example, if the input is
 *
 *     A#C#D
 *     ^
 * The returned pointer points to `C`.
 *
 *     A#C#D
 *       ^
 * This allows us to parse consecutive pitch classes. If parsing failed, the
 * returned pointer is NULL.
 */
const char *pitch_parse_pc(const char *s, struct pitch_class *out);

/*
 * An invertible representation of (tonal) pitch, which is simply a pitch class
 * with an octave.
 */
struct pitch {
  struct pitch_class pc;
  int octave;
};

/* Convert pitch to midi index (can be negative) */
int pitch_to_midi(struct pitch pitch);
/*
 * Parse pitch from s.
 *
 * The returned points after the last valid token. For example, if the input is
 *
 *     A#1C#D3
 *     ^
 * The returned pointer points to `C`.
 *
 *     A#1C#D3
 *        ^
 * This allows us to parse consecutive pitches. If parsing failed, the returned
 * pointer is NULL.
 *
 * If a pitch does not have an octave, the default is 0.
 */
const char *pitch_parse(const char *s, struct pitch *out);

#endif
