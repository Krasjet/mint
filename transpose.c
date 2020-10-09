#include "mint.h"
#include "pitch.h"
#include "transpose.h"

static int
mod(int a, int n)
{
  /* make sure the result is in Zn */
  return (a % n + n) % n;
}

struct pitch
transpose_pitch(struct pitch p, struct mint intv, enum transpose_dir direction)
{
  /*
   * basic idea:
   *   1. transpose pitch chromatically
   *   2. transpose pitch diatonically
   *   3. compare difference to get the accidental
   */
  int chromatic = pitch_to_midi(p) + direction * mint_to_st(intv);
  int diatonic = p.pc.letter + direction * intv.size;

  /* new pitch without accidental */
  p.octave += diatonic / 7;
  if (diatonic < 0){
    /* always round down */
    p.octave--;
  }
  p.pc.letter = mod(diatonic, 7);
  p.pc.accidental = 0;

  /* compare difference */
  p.pc.accidental = chromatic - pitch_to_midi(p);

  return p;
}

struct pitch_class
transpose_pc(struct pitch_class pc, struct mint intv, enum transpose_dir direction)
{
  /*
   * Our representation is not ideal for working with pitch classes alone since
   * equivalent classes are flat.
   *
   * Using circle of fifth could make this much simpler.
   */
  struct pitch p = {
    .pc = pc,
    .octave = 0
  };

  return transpose_pitch(p, intv, direction).pc;
}
