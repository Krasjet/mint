#include "mint.h"
#include <stdio.h>
#include <stdlib.h>

typedef int (*comparator)(int, int);

int eq(int x, int y) { return x == y; }
int lt(int x, int y) { return x < y; }

void
expect(comparator cmp, int x, int y)
{
  if (cmp(x, y)) {
    fputs("✓", stdout);
  } else{
    printf("✗\n%d %d\n", x, y);
    exit(1);
  }
}

void
it(const char* s)
{
  printf("it %s ", s);
}

void
end(void)
{
  puts("");
}

int
main(void)
{
  it("parses dd1 as MINT_MIN");
    expect(eq, mint_parse("dd1"), MINT_MIN);
  end();

  it("parses simple intervals correctly");
    expect(eq, mint_parse("dd1"), -2);
    expect(eq, mint_parse("d1"), -1);
    expect(eq, mint_parse("P1"), 0);
    expect(eq, mint_parse("A1"), 1);
    expect(eq, mint_parse("AA1"), 2);
    expect(eq, mint_parse("m2"), 1);
    expect(eq, mint_parse("M2"), 2);
    expect(eq, mint_parse("A3"), 5);
    expect(eq, mint_parse("P4"), 5);
    expect(eq, mint_parse("dd5"), 5);
    expect(eq, mint_parse("d5"), 6);
    expect(eq, mint_parse("P5"), 7);
    expect(eq, mint_parse("A5"), 8);
    expect(eq, mint_parse("AA5"), 9);
    expect(eq, mint_parse("dd6"), 6);
    expect(eq, mint_parse("d6"), 7);
    expect(eq, mint_parse("m6"), 8);
    expect(eq, mint_parse("M6"), 9);
    expect(eq, mint_parse("A6"), 10);
    expect(eq, mint_parse("AA6"), 11);
  end();

  it("parses compound intervals correctly");
    expect(eq, mint_parse("dd8"), 10);
    expect(eq, mint_parse("d8"), 11);
    expect(eq, mint_parse("P8"), 12);
    expect(eq, mint_parse("A8"), 13);
    expect(eq, mint_parse("AA8"), 14);
    expect(eq, mint_parse("dd9"), 11);
    expect(eq, mint_parse("d9"), 12);
    expect(eq, mint_parse("m9"), 13);
    expect(eq, mint_parse("M9"), 14);
    expect(eq, mint_parse("A9"), 15);
    expect(eq, mint_parse("AA9"), 16);
    /* just in case */
    expect(eq, mint_parse("dd15"), 22);
    expect(eq, mint_parse("d15"), 23);
    expect(eq, mint_parse("P15"), 24);
    expect(eq, mint_parse("A15"), 25);
    expect(eq, mint_parse("AA15"), 26);
  end();

  it("fails on invalid input");
    expect(lt, mint_parse("D1"), MINT_MIN);
    expect(lt, mint_parse("a1"), MINT_MIN);
    expect(lt, mint_parse("M0"), MINT_MIN);
    expect(lt, mint_parse("AA0"), MINT_MIN);
    expect(lt, mint_parse("d-1"), MINT_MIN);
    expect(lt, mint_parse("-d1"), MINT_MIN);
    expect(lt, mint_parse(""), MINT_MIN);
    expect(lt, mint_parse(" "), MINT_MIN);
  end();

  it("fails on type mismatch");
    expect(lt, mint_parse("M1"), MINT_MIN);
    expect(lt, mint_parse("m1"), MINT_MIN);
    expect(lt, mint_parse("P2"), MINT_MIN);
    expect(lt, mint_parse("P3"), MINT_MIN);
    expect(lt, mint_parse("M4"), MINT_MIN);
    expect(lt, mint_parse("m4"), MINT_MIN);
    expect(lt, mint_parse("M5"), MINT_MIN);
    expect(lt, mint_parse("m5"), MINT_MIN);
    expect(lt, mint_parse("P6"), MINT_MIN);
    expect(lt, mint_parse("P7"), MINT_MIN);
    expect(lt, mint_parse("m8"), MINT_MIN);
  end();

  return 0;
}
