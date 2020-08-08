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
    expect(eq, parse_interval("dd1"), MINT_MIN);
  end();

  it("parses simple intervals correctly");
    expect(eq, parse_interval("dd1"), -2);
    expect(eq, parse_interval("d1"), -1);
    expect(eq, parse_interval("P1"), 0);
    expect(eq, parse_interval("A1"), 1);
    expect(eq, parse_interval("AA1"), 2);
    expect(eq, parse_interval("m2"), 1);
    expect(eq, parse_interval("M2"), 2);
    expect(eq, parse_interval("A3"), 5);
    expect(eq, parse_interval("P4"), 5);
    expect(eq, parse_interval("dd5"), 5);
    expect(eq, parse_interval("d5"), 6);
    expect(eq, parse_interval("P5"), 7);
    expect(eq, parse_interval("A5"), 8);
    expect(eq, parse_interval("AA5"), 9);
    expect(eq, parse_interval("dd6"), 6);
    expect(eq, parse_interval("d6"), 7);
    expect(eq, parse_interval("m6"), 8);
    expect(eq, parse_interval("M6"), 9);
    expect(eq, parse_interval("A6"), 10);
    expect(eq, parse_interval("AA6"), 11);
  end();

  it("parses compound intervals correctly");
    expect(eq, parse_interval("dd8"), 10);
    expect(eq, parse_interval("d8"), 11);
    expect(eq, parse_interval("P8"), 12);
    expect(eq, parse_interval("A8"), 13);
    expect(eq, parse_interval("AA8"), 14);
    expect(eq, parse_interval("dd9"), 11);
    expect(eq, parse_interval("d9"), 12);
    expect(eq, parse_interval("m9"), 13);
    expect(eq, parse_interval("M9"), 14);
    expect(eq, parse_interval("A9"), 15);
    expect(eq, parse_interval("AA9"), 16);
    /* just in case */
    expect(eq, parse_interval("dd15"), 22);
    expect(eq, parse_interval("d15"), 23);
    expect(eq, parse_interval("P15"), 24);
    expect(eq, parse_interval("A15"), 25);
    expect(eq, parse_interval("AA15"), 26);
  end();

  it("fails on invalid input");
    expect(lt, parse_interval("D1"), MINT_MIN);
    expect(lt, parse_interval("a1"), MINT_MIN);
    expect(lt, parse_interval("M0"), MINT_MIN);
    expect(lt, parse_interval("AA0"), MINT_MIN);
    expect(lt, parse_interval("d-1"), MINT_MIN);
    expect(lt, parse_interval("-d1"), MINT_MIN);
    expect(lt, parse_interval(""), MINT_MIN);
    expect(lt, parse_interval(" "), MINT_MIN);
  end();

  it("fails on type mismatch");
    expect(lt, parse_interval("M1"), MINT_MIN);
    expect(lt, parse_interval("m1"), MINT_MIN);
    expect(lt, parse_interval("P2"), MINT_MIN);
    expect(lt, parse_interval("P3"), MINT_MIN);
    expect(lt, parse_interval("M4"), MINT_MIN);
    expect(lt, parse_interval("m4"), MINT_MIN);
    expect(lt, parse_interval("M5"), MINT_MIN);
    expect(lt, parse_interval("m5"), MINT_MIN);
    expect(lt, parse_interval("P6"), MINT_MIN);
    expect(lt, parse_interval("P7"), MINT_MIN);
    expect(lt, parse_interval("m8"), MINT_MIN);
  end();

  return 0;
}
