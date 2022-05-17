#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>

typedef struct {
  char r;
  char g;
  char b;
} Color;

void writePPM(FILE *file, Color *framebuffer, int width, int height);

#endif