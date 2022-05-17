#include "image.h"

void writePPM(FILE *file, Color *framebuffer, int width, int height) {
  fprintf(file, "P6\n%d %d\n255\n", width, height);
  for(int i = 0; i < width * height; i++) {
    fwrite(&framebuffer[i], sizeof(Color), 1, file);
  }
}