#ifndef TEST_H
#define TEST_H

#include <stdio.h>

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

#endif
