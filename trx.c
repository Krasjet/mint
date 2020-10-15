#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pitch.h"
#include "mint.h"
#include "transpose.h"

enum {
  /* seriously, a 1024 character long interval? */
  MAX_LEN = 1024
};

void
die(const char *msg)
{
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

int
abs(int x)
{
  return x < 0 ? -x : x;
}

int
readw(char *out, size_t bufsiz)
{
  int ch;
  size_t count = 0;

  while ((ch = fgetc(stdin)) != EOF) {
    if (count >= bufsiz) {
      return 0;
    }
    if (isspace(ch)) {
      if (count == 0) {
        continue;
      } else {
        *out = '\0';
        return 1;
      }
    }
    *out++ = ch;
    count++;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  char interval[MAX_LEN];
  char *s;
  struct mint mint;
  struct pitch p, pnew;

  if (argc < 2) {
    printf("usage: echo intervals | %s note\n", argv[0]);
    return 1;
  }

  if (!pitch_parse(argv[1], &p)) {
    die("invalid pitch");
  }

  while (readw(interval, MAX_LEN)) {
    mint = mint_parse(interval);

    if (mint.size < 0) {
      die("invalid interval");
    }

    pnew = transpose_pitch(p, mint, DIR_UPWARD);

    s = malloc(abs(pnew.pc.accidental) + 2);
      if(!s) {
        die("out of memory");
      }
      pitch_pc_to_ascii(pnew.pc, s);
      printf("%s ", s);
    free(s);

    /* for building scales */
    /* note = newnote; */
  }
  puts("");

  return 0;
}
