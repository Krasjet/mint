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
expectfail(mint_t intv)
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
  describe("mint_from_str");
    it("parses simple intervals correctly");
      mint_t dd1 = mint_from_str("dd1");
      expecteq(dd1.quality, MINT_DOUBLY_DIMINISHED);
      expecteq(dd1.size, 0);

      mint_t d1 = mint_from_str("d1");
      expecteq(d1.quality, MINT_DIMINISHED);
      expecteq(d1.size, 0);

      mint_t P1 = mint_from_str("P1");
      expecteq(P1.quality, MINT_PERFECT);
      expecteq(P1.size, 0);

      mint_t A1 = mint_from_str("A1");
      expecteq(A1.quality, MINT_AUGMENTED);
      expecteq(A1.size, 0);

      mint_t AA1 = mint_from_str("AA1");
      expecteq(AA1.quality, MINT_DOUBLY_AUGMENTED);
      expecteq(AA1.size, 0);

      mint_t m3 = mint_from_str("m3");
      expecteq(m3.quality, MINT_MINOR);
      expecteq(m3.size, 2);

      mint_t M3 = mint_from_str("M3");
      expecteq(M3.quality, MINT_MAJOR);
      expecteq(M3.size, 2);
    end();

    it("parses compound intervals correctly");
      mint_t dd8 = mint_from_str("dd8");
      expecteq(dd8.quality, MINT_DOUBLY_DIMINISHED);
      expecteq(dd8.size, 7);

      mint_t d8 = mint_from_str("d8");
      expecteq(d8.quality, MINT_DIMINISHED);
      expecteq(d8.size, 7);

      mint_t P8 = mint_from_str("P8");
      expecteq(P8.quality, MINT_PERFECT);
      expecteq(P8.size, 7);

      mint_t A8 = mint_from_str("A8");
      expecteq(A8.quality, MINT_AUGMENTED);
      expecteq(A8.size, 7);

      mint_t AA8 = mint_from_str("AA8");
      expecteq(AA8.quality, MINT_DOUBLY_AUGMENTED);
      expecteq(AA8.size, 7);

      mint_t m9 = mint_from_str("m9");
      expecteq(m9.quality, MINT_MINOR);
      expecteq(m9.size, 8);

      mint_t M9 = mint_from_str("M9");
      expecteq(M9.quality, MINT_MAJOR);
      expecteq(M9.size, 8);

      /* just in case */
      mint_t P15 = mint_from_str("P15");
      expecteq(P15.quality, MINT_PERFECT);
      expecteq(P15.size, 14);
    end();

    it("fails on invalid input");
      expectfail(mint_from_str("D1"));
      expectfail(mint_from_str("a1"));
      expectfail(mint_from_str("M0"));
      expectfail(mint_from_str("AA0"));
      expectfail(mint_from_str("d-1"));
      expectfail(mint_from_str("-d1"));
      expectfail(mint_from_str(""));
      expectfail(mint_from_str(" "));
    end();

    it("fails on type mismatch");
      expectfail(mint_from_str("M1"));
      expectfail(mint_from_str("m1"));
      expectfail(mint_from_str("P2"));
      expectfail(mint_from_str("P3"));
      expectfail(mint_from_str("M4"));
      expectfail(mint_from_str("m4"));
      expectfail(mint_from_str("M5"));
      expectfail(mint_from_str("m5"));
      expectfail(mint_from_str("P6"));
      expectfail(mint_from_str("P7"));
      expectfail(mint_from_str("m8"));
    end();
  end();

  describe("mint_qualoffset");
    it("gets offset for perfectable interval correctly");
      expecteq(mint_qualoffset(MINT_PERFECT, 0), 0);
      expecteq(mint_qualoffset(MINT_AUGMENTED, 0), 1);
      expecteq(mint_qualoffset(MINT_DOUBLY_AUGMENTED, 0), 2);
      expecteq(mint_qualoffset(MINT_DIMINISHED, 0), -1);
      expecteq(mint_qualoffset(MINT_DOUBLY_DIMINISHED, 0), -2);
    end();

    it("gets offset for nonperfectable interval correctly");
      expecteq(mint_qualoffset(MINT_MAJOR, 2), 0);
      expecteq(mint_qualoffset(MINT_MINOR, 2), -1);
      expecteq(mint_qualoffset(MINT_AUGMENTED, 2), 1);
      expecteq(mint_qualoffset(MINT_DOUBLY_AUGMENTED, 2), 2);
      expecteq(mint_qualoffset(MINT_DIMINISHED, 2), -2);
      expecteq(mint_qualoffset(MINT_DOUBLY_DIMINISHED, 2), -3);
    end();
  end();

  describe("mint_to_st");
    it("converts simple intervals correctly");
      expecteq(mint_to_st(mint_from_str("dd1")), -2);
      expecteq(mint_to_st(mint_from_str("d1")), -1);
      expecteq(mint_to_st(mint_from_str("P1")), 0);
      expecteq(mint_to_st(mint_from_str("A1")), 1);
      expecteq(mint_to_st(mint_from_str("AA1")), 2);
      expecteq(mint_to_st(mint_from_str("m2")), 1);
      expecteq(mint_to_st(mint_from_str("M2")), 2);
      expecteq(mint_to_st(mint_from_str("A3")), 5);
      expecteq(mint_to_st(mint_from_str("P4")), 5);
      expecteq(mint_to_st(mint_from_str("dd5")), 5);
      expecteq(mint_to_st(mint_from_str("d5")), 6);
      expecteq(mint_to_st(mint_from_str("P5")), 7);
      expecteq(mint_to_st(mint_from_str("A5")), 8);
      expecteq(mint_to_st(mint_from_str("AA5")), 9);
      expecteq(mint_to_st(mint_from_str("dd6")), 6);
      expecteq(mint_to_st(mint_from_str("d6")), 7);
      expecteq(mint_to_st(mint_from_str("m6")), 8);
      expecteq(mint_to_st(mint_from_str("M6")), 9);
      expecteq(mint_to_st(mint_from_str("A6")), 10);
      expecteq(mint_to_st(mint_from_str("AA6")), 11);
    end();

    it("converts compound intervals correctly");
      expecteq(mint_to_st(mint_from_str("dd8")), 10);
      expecteq(mint_to_st(mint_from_str("d8")), 11);
      expecteq(mint_to_st(mint_from_str("P8")), 12);
      expecteq(mint_to_st(mint_from_str("A8")), 13);
      expecteq(mint_to_st(mint_from_str("AA8")), 14);
      expecteq(mint_to_st(mint_from_str("dd9")), 11);
      expecteq(mint_to_st(mint_from_str("d9")), 12);
      expecteq(mint_to_st(mint_from_str("m9")), 13);
      expecteq(mint_to_st(mint_from_str("M9")), 14);
      expecteq(mint_to_st(mint_from_str("A9")), 15);
      expecteq(mint_to_st(mint_from_str("AA9")), 16);
      expecteq(mint_to_st(mint_from_str("dd15")), 22);
      expecteq(mint_to_st(mint_from_str("d15")), 23);
      expecteq(mint_to_st(mint_from_str("P15")), 24);
      expecteq(mint_to_st(mint_from_str("A15")), 25);
      expecteq(mint_to_st(mint_from_str("AA15")), 26);
    end();

    it("converts readme example correctly");
      expecteq(mint_to_st(mint_from_str("M3")), 4);
      expecteq(mint_to_st(mint_from_str("m3")), 3);
      expecteq(mint_to_st(mint_from_str("A3")), 5);
      expecteq(mint_to_st(mint_from_str("d3")), 2);
    end();
  end();

  return 0;
}
