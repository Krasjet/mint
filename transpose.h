/* This module dependes on pitch and mint */

#ifndef TRANSPOSE_H
#define TRANSPOSE_H

struct pitch;
struct mint;

enum transpose_dir {
  DIR_UPWARD = 1,
  DIR_DOWNWARD = -1
};

/* Transpose pitch by interval */
struct pitch transpose_pitch(struct pitch p,
    struct mint intv, enum transpose_dir direction);

/* Transpose pitch class by interval */
struct pitch_class transpose_pc(struct pitch_class pc,
    struct mint intv, enum transpose_dir direction);

#endif
