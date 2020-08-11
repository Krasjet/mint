#include "mint.h"
#include <stdio.h>
#include <stdlib.h>

void
expecteq(int x, int y)
{
  if (x == y) {
    fputs("✓", stdout);
  } else{
    printf("✗\n%d %d\n", x, y);
    exit(1);
  }
}

void
expectfail(struct mint intv)
{
  if (intv.size < 0) {
    fputs("✓", stdout);
  } else {
    printf("✗\nparsing should've failed");
    exit(1);
  }
}

void
describe(const char* s)
{
  puts(s);
}

void
it(const char* s)
{
  printf("  it %s ", s);
}

void
end(void)
{
  puts("");
}

int
main(void)
{
  describe("mint_get_quality");
    it("gets quality for perfectable interval correctly");
      expecteq(mint_get_quality((struct mint) {0, 0}), MINT_PERFECT);
      expecteq(mint_get_quality((struct mint) {0, 1}), MINT_AUGMENTED);
      expecteq(mint_get_quality((struct mint) {0, 2}), MINT_DOUBLY_AUGMENTED);
      expecteq(mint_get_quality((struct mint) {0, -1}), MINT_DIMINISHED);
      expecteq(mint_get_quality((struct mint) {0, -2}), MINT_DOUBLY_DIMINISHED);
    end();

    it("gets quality for nonperfectable interval correctly");
      expecteq(mint_get_quality((struct mint) {2, 0}), MINT_MAJOR);
      expecteq(mint_get_quality((struct mint) {2, -1}), MINT_MINOR);
      expecteq(mint_get_quality((struct mint) {2, 1}), MINT_AUGMENTED);
      expecteq(mint_get_quality((struct mint) {2, 2}), MINT_DOUBLY_AUGMENTED);
      expecteq(mint_get_quality((struct mint) {2, -2}), MINT_DIMINISHED);
      expecteq(mint_get_quality((struct mint) {2, -3}), MINT_DOUBLY_DIMINISHED);
    end();
  end();

  describe("mint_qoffset");
    it("gets offset for perfectable interval correctly");
      expecteq(mint_qoffset(MINT_PERFECT, 0), 0);
      expecteq(mint_qoffset(MINT_AUGMENTED, 0), 1);
      expecteq(mint_qoffset(MINT_DOUBLY_AUGMENTED, 0), 2);
      expecteq(mint_qoffset(MINT_DIMINISHED, 0), -1);
      expecteq(mint_qoffset(MINT_DOUBLY_DIMINISHED, 0), -2);
    end();

    it("gets offset for nonperfectable interval correctly");
      expecteq(mint_qoffset(MINT_MAJOR, 2), 0);
      expecteq(mint_qoffset(MINT_MINOR, 2), -1);
      expecteq(mint_qoffset(MINT_AUGMENTED, 2), 1);
      expecteq(mint_qoffset(MINT_DOUBLY_AUGMENTED, 2), 2);
      expecteq(mint_qoffset(MINT_DIMINISHED, 2), -2);
      expecteq(mint_qoffset(MINT_DOUBLY_DIMINISHED, 2), -3);
    end();
  end();

  describe("mint_parse");
    it("parses simple intervals correctly");
      struct mint dd1 = mint_parse("dd1");
      expecteq(mint_get_quality(dd1), MINT_DOUBLY_DIMINISHED);
      expecteq(dd1.size, 0);

      struct mint d1 = mint_parse("d1");
      expecteq(mint_get_quality(d1), MINT_DIMINISHED);
      expecteq(d1.size, 0);

      struct mint P1 = mint_parse("P1");
      expecteq(mint_get_quality(P1), MINT_PERFECT);
      expecteq(P1.size, 0);

      struct mint A1 = mint_parse("A1");
      expecteq(mint_get_quality(A1), MINT_AUGMENTED);
      expecteq(A1.size, 0);

      struct mint AA1 = mint_parse("AA1");
      expecteq(mint_get_quality(AA1), MINT_DOUBLY_AUGMENTED);
      expecteq(AA1.size, 0);

      struct mint m3 = mint_parse("m3");
      expecteq(mint_get_quality(m3), MINT_MINOR);
      expecteq(m3.size, 2);

      struct mint M3 = mint_parse("M3");
      expecteq(mint_get_quality(M3), MINT_MAJOR);
      expecteq(M3.size, 2);
    end();

    it("parses compound intervals correctly");
      struct mint dd8 = mint_parse("dd8");
      expecteq(mint_get_quality(dd8), MINT_DOUBLY_DIMINISHED);
      expecteq(dd8.size, 7);

      struct mint d8 = mint_parse("d8");
      expecteq(mint_get_quality(d8), MINT_DIMINISHED);
      expecteq(d8.size, 7);

      struct mint P8 = mint_parse("P8");
      expecteq(mint_get_quality(P8), MINT_PERFECT);
      expecteq(P8.size, 7);

      struct mint A8 = mint_parse("A8");
      expecteq(mint_get_quality(A8), MINT_AUGMENTED);
      expecteq(A8.size, 7);

      struct mint AA8 = mint_parse("AA8");
      expecteq(mint_get_quality(AA8), MINT_DOUBLY_AUGMENTED);
      expecteq(AA8.size, 7);

      struct mint m9 = mint_parse("m9");
      expecteq(mint_get_quality(m9), MINT_MINOR);
      expecteq(m9.size, 8);

      struct mint M9 = mint_parse("M9");
      expecteq(mint_get_quality(M9), MINT_MAJOR);
      expecteq(M9.size, 8);

      /* just in case */
      struct mint P15 = mint_parse("P15");
      expecteq(mint_get_quality(P15), MINT_PERFECT);
      expecteq(P15.size, 14);
    end();

    it("fails on invalid input");
      expectfail(mint_parse("D1"));
      expectfail(mint_parse("a1"));
      expectfail(mint_parse("M0"));
      expectfail(mint_parse("AA0"));
      expectfail(mint_parse("d-1"));
      expectfail(mint_parse("-d1"));
      expectfail(mint_parse(""));
      expectfail(mint_parse(" "));
    end();

    it("fails on type mismatch");
      expectfail(mint_parse("M1"));
      expectfail(mint_parse("m1"));
      expectfail(mint_parse("P2"));
      expectfail(mint_parse("P3"));
      expectfail(mint_parse("M4"));
      expectfail(mint_parse("m4"));
      expectfail(mint_parse("M5"));
      expectfail(mint_parse("m5"));
      expectfail(mint_parse("P6"));
      expectfail(mint_parse("P7"));
      expectfail(mint_parse("m8"));
    end();
  end();

  describe("mint_to_st");
    it("converts simple intervals correctly");
      expecteq(mint_to_st(mint_parse("dd1")), -2);
      expecteq(mint_to_st(mint_parse("d1")), -1);
      expecteq(mint_to_st(mint_parse("P1")), 0);
      expecteq(mint_to_st(mint_parse("A1")), 1);
      expecteq(mint_to_st(mint_parse("AA1")), 2);
      expecteq(mint_to_st(mint_parse("m2")), 1);
      expecteq(mint_to_st(mint_parse("M2")), 2);
      expecteq(mint_to_st(mint_parse("A3")), 5);
      expecteq(mint_to_st(mint_parse("P4")), 5);
      expecteq(mint_to_st(mint_parse("dd5")), 5);
      expecteq(mint_to_st(mint_parse("d5")), 6);
      expecteq(mint_to_st(mint_parse("P5")), 7);
      expecteq(mint_to_st(mint_parse("A5")), 8);
      expecteq(mint_to_st(mint_parse("AA5")), 9);
      expecteq(mint_to_st(mint_parse("dd6")), 6);
      expecteq(mint_to_st(mint_parse("d6")), 7);
      expecteq(mint_to_st(mint_parse("m6")), 8);
      expecteq(mint_to_st(mint_parse("M6")), 9);
      expecteq(mint_to_st(mint_parse("A6")), 10);
      expecteq(mint_to_st(mint_parse("AA6")), 11);
    end();

    it("converts compound intervals correctly");
      expecteq(mint_to_st(mint_parse("dd8")), 10);
      expecteq(mint_to_st(mint_parse("d8")), 11);
      expecteq(mint_to_st(mint_parse("P8")), 12);
      expecteq(mint_to_st(mint_parse("A8")), 13);
      expecteq(mint_to_st(mint_parse("AA8")), 14);
      expecteq(mint_to_st(mint_parse("dd9")), 11);
      expecteq(mint_to_st(mint_parse("d9")), 12);
      expecteq(mint_to_st(mint_parse("m9")), 13);
      expecteq(mint_to_st(mint_parse("M9")), 14);
      expecteq(mint_to_st(mint_parse("A9")), 15);
      expecteq(mint_to_st(mint_parse("AA9")), 16);
      expecteq(mint_to_st(mint_parse("dd15")), 22);
      expecteq(mint_to_st(mint_parse("d15")), 23);
      expecteq(mint_to_st(mint_parse("P15")), 24);
      expecteq(mint_to_st(mint_parse("A15")), 25);
      expecteq(mint_to_st(mint_parse("AA15")), 26);
    end();

    it("converts readme example correctly");
      expecteq(mint_to_st(mint_parse("M3")), 4);
      expecteq(mint_to_st(mint_parse("m3")), 3);
      expecteq(mint_to_st(mint_parse("A3")), 5);
      expecteq(mint_to_st(mint_parse("d3")), 2);
    end();
  end();

  return 0;
}
