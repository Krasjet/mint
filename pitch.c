#include "pitch.h"

static int step_semitones[] = {
  [PITCH_C] = 0,
  [PITCH_D] = 2,
  [PITCH_E] = 4,
  [PITCH_F] = 5,
  [PITCH_G] = 7,
  [PITCH_A] = 9,
  [PITCH_B] = 11
};

char
pitch_letter_to_char(enum pitch_letter l){
  static int ch_lookup[] = {
    [PITCH_C] = 'C',
    [PITCH_D] = 'D',
    [PITCH_E] = 'E',
    [PITCH_F] = 'F',
    [PITCH_G] = 'G',
    [PITCH_A] = 'A',
    [PITCH_B] = 'B'
  };
  return ch_lookup[l];
}

enum pitch_letter
pitch_char_to_letter(char ch)
{
  static enum pitch_letter letter_lookup[] = {
    [0] = PITCH_A,
    [1] = PITCH_B,
    [2] = PITCH_C,
    [3] = PITCH_D,
    [4] = PITCH_E,
    [5] = PITCH_F,
    [6] = PITCH_G
  };
  return letter_lookup[ch - 'A'];
}

static int
count_ch(const char *s, char ch)
{
  int count = 0;
  while (*s++ == ch) {
    ++count;
  }
  return count;
}

const char *
pitch_parse_pc(const char *s, struct pitch_class *out)
{
  /* letter */
  if ((unsigned)(*s - 'A') < 7)
    out->letter = pitch_char_to_letter(*s++);
  else
    return 0;

  /* accidental */
  switch (*s) {
  case '#':
    out->accidental = count_ch(s, '#');
    s += out->accidental;
    break;
  case 'b':
    out->accidental = -count_ch(s, 'b');
    s -= out->accidental;
    break;
  case 'x':
    out->accidental = 2;
    s++;
    break;
  default:
    out->accidental = 0;
  }

  return s;
}

void
pitch_pc_to_ascii(struct pitch_class pc, char *out)
{
  int acc = pc.accidental;

  *out++ = pitch_letter_to_char(pc.letter);

  if (acc > 0) {
    if (acc == 2) {
      /* double sharp */
      *out++ = 'x';
    } else {
      while(acc-- > 0){
        *out++ = '#';
      }
    }
  } else if (acc < 0) {
    while(acc++ < 0){
      *out++ = 'b';
    }
  }
  *out = '\0';
}

const char *
pitch_parse(const char* s, struct pitch *out)
{
  /* -1 for positive, 1 for negative*/
  int negative = -1;

  s = pitch_parse_pc(s, &out->pc);
  if (!s)
    return 0;

  /* octave, can be negative */
  if (*s == '-') {
    negative = 1;
    s++;
  }
  out->octave = 0;
  while ((unsigned)(*s - '0') < 10)
    out->octave = 10 * out->octave - (*s++ - '0');

  out->octave *= negative;

  return s;
}

int
pitch_pc_to_idx(struct pitch_class pc){
  return step_semitones[pc.letter] + pc.accidental;
}

int
pitch_to_midi(struct pitch p)
{
  return pitch_pc_to_idx(p.pc) + 12 * (p.octave + 2);
}
