#include <stdlib.h>
#include "test.h"
#include "pitch.h"

void
expect_pitch_eq(struct pitch x, struct pitch y)
{
  if (x.octave != y.octave) {
    printf("✗\noctave: %d %d\n", x.octave, y.octave);
    exit(1);
  }

  if (x.pc.letter != y.pc.letter) {
    printf("✗\nletter: %c %c\n",
        pitch_letter_to_char(x.pc.letter),
        pitch_letter_to_char(y.pc.letter)
    );
    exit(1);
  }

  if (x.pc.accidental != y.pc.accidental) {
    printf("✗\accidental: %d %d\n", x.pc.accidental, y.pc.accidental);
    exit(1);
  }

  fputs("✓", stdout);
}

void
expect_pitch_fail(char * ptr)
{
  if (ptr == NULL) {
    fputs("✓", stdout);
  } else {
    printf("✗\nparsing should've failed");
    exit(1);
  }
}

int
main(void)
{
  struct pitch expect, actual;
  describe("pitch_parse");
    it("parses pitches without accidental");
      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_A,
          .accidental = 0
        },
        .octave = 1
      };
      pitch_parse("A1", &actual);
      expect_pitch_eq(actual, expect);
    end();

    it("defaults octave to 0");
      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_A,
          .accidental = 0
        },
        .octave = 0
      };
      pitch_parse("A", &actual);
      expect_pitch_eq(actual, expect);
    end();

    it("allows negative octaves");
      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_A,
          .accidental = 0
        },
        .octave = -1
      };
      pitch_parse("A-1", &actual);
      expect_pitch_eq(actual, expect);
    end();

    it("parses accidental correctly");
      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_A,
          .accidental = 1
        },
        .octave = 0
      };
      pitch_parse("A#", &actual);
      expect_pitch_eq(actual, expect);

      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_A,
          .accidental = 2
        },
        .octave = 0
      };
      pitch_parse("Ax", &actual);
      expect_pitch_eq(actual, expect);
      pitch_parse("A##", &actual);
      expect_pitch_eq(actual, expect);

      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_C,
          .accidental = -1
        },
        .octave = 0
      };
      pitch_parse("Cb", &actual);
      expect_pitch_eq(actual, expect);

      expect = (struct pitch) {
        .pc = {
          .letter = PITCH_C,
          .accidental = -2
        },
        .octave = -1
      };
      pitch_parse("Cbb-1", &actual);
      expect_pitch_eq(actual, expect);
    end();
  end();
  return 0;
}
