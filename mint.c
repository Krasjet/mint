#include "mint.h"

/* only unison, 4th, 5th can be perfect */
static int perfectable[] = { 1, 0, 0, 1, 1, 0, 0};

static int base[] = {
  0, /* P1 */
  2, /* M2 */
  4, /* M3 */
  5, /* P4 */
  7, /* P5 */
  9, /* M6 */
  11 /* M7 */
};

static int qual_transfm[] = {
  [MINT_DOUBLY_DIMINISHED] = -3,
  [MINT_DIMINISHED] = -2,
  [MINT_MINOR] = -1,
  [MINT_MAJOR] = 0,
  [MINT_PERFECT] = 0,
  [MINT_AUGMENTED] = 1,
  [MINT_DOUBLY_AUGMENTED] = 2
};

mint_t
mint_from_str(const char* s)
{
  mint_t intv = {
    .size = 0
  };
  /* -1 = ignored */
  int perfect = -1;

  /* valid qualifiers: P, M, m, A, AA, d, dd */
  switch (*s++) {
    case 'P':
      intv.quality = MINT_PERFECT;
      perfect = 1;
      break;
    case 'M':
      intv.quality = MINT_MAJOR;
      perfect = 0;
      break;
    case 'm':
      intv.quality = MINT_MINOR;
      perfect = 0;
      break;
    case 'A':
      if (*s == 'A') {
        intv.quality = MINT_DOUBLY_AUGMENTED;
        s++;
      } else {
        intv.quality = MINT_AUGMENTED;
      }
      break;
    case 'd':
      if (*s == 'd') {
        intv.quality = MINT_DOUBLY_DIMINISHED;
        s++;
      } else {
        intv.quality = MINT_DIMINISHED;
      }
      break;
    default:
      goto fail;
  }

  /* parse nonnegative integer */
  while ((unsigned)(*s - '0') < 10)
    intv.size = 10 * intv.size + (*s++ - '0');

  if (--intv.size < 0)
    /* we don't support negative intervals */
    goto fail;

  if (perfect != -1 && perfect != perfectable[intv.size % 7]) {
    /* type mismatch */
    goto fail;
  }

  return intv;
fail:
  intv.size = -1;
  return intv;
}

int
mint_to_semitone(mint_t interval)
{
  /* handle compound intervals */
  int octave = interval.size / 7;
  int n = interval.size % 7;

  int trans = qual_transfm[interval.quality];

  if (perfectable[n] && interval.quality <= MINT_DIMINISHED){
    /* perfect intervals only shift by 1 when diminished */
    trans++;
  }
  return 12 * octave + base[n] + trans;
}
