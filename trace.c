#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vector.h"
#include "image.h"
#include "scene.h"
#include "sphere.h"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define FOV 50 //50 deg

float deg2rad(float deg) {
  return deg * 3.14159 / 180.;
}

void createCameraRay(Ray *ray, int px, int py, float imageAspectRatio, float frameWidth) {
  float pixelNDCX = (2.0 * ((float) px + 0.5)) / ((float) IMAGE_WIDTH - 1);
  float pixelNDCY = (1.0 - 2.0 * ((float) py + 0.5)) / ((float) IMAGE_HEIGHT);

  float pixelCameraX = pixelNDCX * frameWidth * imageAspectRatio;
  float pixelCameraY = pixelNDCY * frameWidth;
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

Color castRay(Ray *ray, Scene *scene) {
  Color result = {0};
  
  for(int i = 0; i < scene->objectCount; i++) {
    float t;
    if (scene->objects[i].intersect(ray, scene->objects[i].object, &t)) {
      return (Color) {255, 0, 0};
    }
  }
  
  return result;
}

int main() {
  float imageAspectRatio = (float) IMAGE_WIDTH / (float) IMAGE_HEIGHT;
  float frameWidth = tanf(deg2rad((float) FOV) / 2.);

  Color *framebuffer = malloc(IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(Color));

  SceneObject sphere = sphereInit((Vec3f) {4.7, -2.5, -7.}, 1.);

  SceneObject *sceneObjects = (SceneObject *) malloc(sizeof(SceneObject));
  sceneObjects[0] = sphere;

  Scene scene = {
    .objectCount = 1,
    .objects = sceneObjects
  };

  for(int y=0; y < IMAGE_HEIGHT; y++) {
    for(int x=0; x < IMAGE_WIDTH; x++) {
      Ray ray;
      createCameraRay(&ray, x, y, imageAspectRatio, frameWidth);
      int fbIndex = y * IMAGE_WIDTH + x;
      framebuffer[fbIndex] = castRay(&ray, &scene);
    }
  }

  FILE *outPPM = fopen("out.ppm", "wb");
  writePPM(outPPM, framebuffer, IMAGE_WIDTH, IMAGE_HEIGHT);
  fclose(outPPM);
  sceneCleanup(&scene);
  free(framebuffer);
  return 0;
}