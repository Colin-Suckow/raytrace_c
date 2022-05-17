#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vector.h"
#include "image.h"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define FOV 1.39626 //80 deg

typedef struct {
  Vec3f origin;
  Vec3f dir;
} Ray;

bool solveQuadratic(const float a, const float b, const float c, float *x0, float *x1) 
{ 
    float discr = b * b - 4 * a * c; 
    if (discr < 0) return false; 
    else if (discr == 0) *x0 = *x1 = - 0.5 * b / a; 
    else { 
        float q = (b > 0) ? 
            -0.5 * (b + sqrt(discr)) : 
            -0.5 * (b - sqrt(discr)); 
        *x0 = q / a; 
        *x1 = c / q; 
    } 
    if (x0 > x1) {
      float temp = *x0;
      *x0 = *x1;
      *x1 = temp;
    }
 
    return true; 
}

void rayInit(Ray *ray, int px, int py, float imageAspectRatio, float frameWidth) {
  float pixelNDCX = ((float) px + 0.5) / (float) IMAGE_WIDTH;
  float pixelNDCY = ((float) py + 0.5) / (float) IMAGE_HEIGHT;

  float pixelCameraX = (2. * pixelNDCX - 1) * imageAspectRatio * frameWidth;
  float pixelCameraY = 1 - 2. * pixelNDCY * frameWidth;
  Vec3f origin = {
    .x = 0,
    .y = 0,
    .z = 0
  };
  Vec3f direction = {
    .x = pixelCameraX,
    .y = pixelCameraY,
    .z = -1.0
  };
  vec3fNormalize(&direction);
  ray->dir = direction;
  ray->origin = origin;
} 

Color castRay(Ray *ray) {
  Color result = {0};
  result.r = (ray->dir.x + 1) * 128;
  result.g = (ray->dir.y + 1) * 128;
  
  return result;
}

int main() {
  float imageAspectRatio = (float) IMAGE_WIDTH / (float) IMAGE_HEIGHT;
  float frameWidth = tanf(FOV / 2.);

  Color *framebuffer = malloc(IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(Color));

  for(int y=0; y < IMAGE_HEIGHT; y++) {
    for(int x=0; x < IMAGE_WIDTH; x++) {
      Ray ray;
      rayInit(&ray, x, y, imageAspectRatio, frameWidth);
      int fbIndex = y * IMAGE_WIDTH + x;
      framebuffer[fbIndex] = castRay(&ray);
    }
  }

  FILE *outPPM = fopen("out.ppm", "wb");
  writePPM(outPPM, framebuffer, IMAGE_WIDTH, IMAGE_HEIGHT);
  fclose(outPPM);

  free(framebuffer);
  return 0;
}