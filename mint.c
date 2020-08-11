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

struct mint
mint_parse(const char *s)
{
  struct mint intv = {
    .qoffset = 0,
  };
  /* -1 = ignored */
  int perfect = -1, diminished = 0;
  int n = 0;

  /* valid qualifiers: P, M, m, A, AA, d, dd */
  switch (*s++) {
    case 'P':
      perfect = 1;
      break;
    case 'M':
      perfect = 0;
      break;
    case 'm':
      perfect = 0;
      intv.qoffset = -1;
      break;
    case 'A':
      if (*s == 'A') {
        intv.qoffset = 2;
        s++;
      } else {
        intv.qoffset = 1;
      }
      break;
    case 'd':
      diminished = 1;
      if (*s == 'd') {
        intv.qoffset = -3;
        s++;
      } else {
        intv.qoffset = -2;
      }
      break;
    default:
      goto fail;
  }

  /* parse nonnegative integer */
  while ((unsigned)(*s - '0') < 10)
    n = 10 * n + (*s++ - '0');

  if (--n < 0) {
    /* we don't support negative intervals */
    goto fail;
  }

  intv.size = n;
  n = n % 7;

  if (perfect != -1 && perfect != perfectable[n]) {
    /* type mismatch */
    goto fail;
  }

  if (diminished && perfectable[n]) {
    /* perfect intervals only shift by 1 when diminished */
    intv.qoffset++;
  }

  return intv;
fail:
  intv.size = -1;
  return intv;
}

enum mint_quality
mint_get_quality(struct mint interval)
{
  /* query with qoffset + 2 */
  static enum mint_quality perfectable_lookup [] = {
    MINT_DOUBLY_DIMINISHED, /* -2 */
    MINT_DIMINISHED,        /* -1 */
    MINT_PERFECT,           /*  0 */
    MINT_AUGMENTED,         /*  1 */
    MINT_DOUBLY_AUGMENTED   /*  2 */
  };
  /* query with qoffset + 3 */
  static enum mint_quality nonperfectable_lookup [] = {
    MINT_DOUBLY_DIMINISHED, /* -3 */
    MINT_DIMINISHED,        /* -2 */
    MINT_MINOR,             /* -1 */
    MINT_MAJOR,             /*  0 */
    MINT_AUGMENTED,         /*  1 */
    MINT_DOUBLY_AUGMENTED   /*  2 */
  };

  if (perfectable[interval.size % 7])
    return perfectable_lookup[interval.qoffset + 2];

  return nonperfectable_lookup[interval.qoffset + 3];
}


int
mint_qoffset(enum mint_quality qual, int size)
{
  static int offset_base[] = {
    [MINT_DOUBLY_DIMINISHED] = -3,
    [MINT_DIMINISHED] = -2,
    [MINT_MINOR] = -1,
    [MINT_MAJOR] = 0,
    [MINT_PERFECT] = 0,
    [MINT_AUGMENTED] = 1,
    [MINT_DOUBLY_AUGMENTED] = 2
  };

  if (perfectable[size % 7] && qual <= MINT_DIMINISHED){
    /* perfect intervals only shift by 1 when diminished */
    return offset_base[qual] + 1;
  }
  return offset_base[qual];
}

int
mint_to_st(struct mint interval)
{
  return 12 * (interval.size / 7) /* handle compound intervals */
    + base[interval.size % 7]
    + interval.qoffset;
}
