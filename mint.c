#include "mint.h"

enum intv_t {
  Intv_P = 0,    /* perfect */
  Intv_M         /* major/minor */
};

/* only unison, 4th, 5th can be perfect */
static int intv_types[] = {
  Intv_P,
  Intv_M,
  Intv_M,
  Intv_P,
  Intv_P,
  Intv_M,
  Intv_M,
};

static int base[] = {
  0, /* P1 */
  2, /* M2 */
  4, /* M3 */
  5, /* P4 */
  7, /* P5 */
  9, /* M6 */
  11 /* M7 */
};

int
parse_interval(const char* s)
{
  int qual_type = -1;
  int diminished = 0;

  int n = 0;
  int qual_mod = 0;
  int octave = 0;

  /* valid qualifiers: P, M, m, A, AA, d, dd */
  switch (*s++) {
    case 'P':
      qual_type = Intv_P;
      break;
    case 'M':
      qual_type = Intv_M;
      break;
    case 'm':
      qual_type = Intv_M;
      qual_mod = -1;
      break;
    case 'A':
      if (*s == 'A') {
        qual_mod = 2;
        s++;
      } else {
        qual_mod = 1;
      }
      break;
    case 'd':
      diminished = 1;
      if (*s == 'd') {
        qual_mod = -3;
        s++;
      } else {
        qual_mod = -2;
      }
      break;
    default:
      goto fail;
  }

  /* parse integer */
  while ((unsigned)(*s - '0') < 10)
    n = 10 * n + (*s++ - '0');

  if (--n < 0)
    /* we don't support negative intervals */
    goto fail;

  /* handle compound intervals */
  octave = n / 7;
  n = n % 7;

  if (qual_type != -1 && intv_types[n] != qual_type)
    /* type mismatch */
    goto fail;

  if (diminished && intv_types[n] == Intv_P) {
    /* perfect intervals only shift by 1 when diminished */
    qual_mod++;
  }

  return 12 * octave + base[n] + qual_mod;
fail:
  return MINT_MIN - 1;
}
