#include <stdlib.h>
#include "test.h"
#include "pitch.h"
#include "mint.h"
#include "transpose.h"

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

int
main(void)
{
  struct pitch expect, origin;
  describe("transpose_pitch");
    it("transposes simple interval correctly");
      pitch_parse("C0", &origin);
      pitch_parse("C0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("P1"), DIR_UPWARD),
        expect
      );

      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("P1"), DIR_DOWNWARD),
        expect
      );

      pitch_parse("C#0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("A1"), DIR_UPWARD),
        expect
      );

      pitch_parse("Cb0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("A1"), DIR_DOWNWARD),
        expect
      );

      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("d1"), DIR_UPWARD),
        expect
      );

      pitch_parse("C#0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("d1"), DIR_DOWNWARD),
        expect
      );

      pitch_parse("E0", &origin);
      pitch_parse("Gx0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("A3"), DIR_UPWARD),
        expect
      );
    end();

    it("handles octave correctly");
      pitch_parse("Bb0", &origin);
      pitch_parse("D#1", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("A3"), DIR_UPWARD),
        expect
      );

      pitch_parse("Bbbb0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("AA1"), DIR_DOWNWARD),
        expect
      );

      pitch_parse("Cb0", &origin);
      pitch_parse("Ab-1", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("m3"), DIR_DOWNWARD),
        expect
      );

      pitch_parse("Cbbb0", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("dd1"), DIR_UPWARD),
        expect
      );
    end();

    it("handles compound intervals correctly");
      pitch_parse("Bb0", &origin);
      pitch_parse("B1", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("A8"), DIR_UPWARD),
        expect
      );

      pitch_parse("Bbbb-1", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("AA8"), DIR_DOWNWARD),
        expect
      );

      pitch_parse("Cb0", &origin);
      pitch_parse("Ab-2", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("m10"), DIR_DOWNWARD),
        expect
      );

      pitch_parse("Cbbb1", &expect);
      expect_pitch_eq(
        transpose_pitch(origin, mint_parse("dd8"), DIR_UPWARD),
        expect
      );
    end();
  end();
  return 0;
}
