#include <math.h>
#include "vector.h"

float vec3fMagnitude(Vec3f *vec) {
  return sqrtf((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
}

void vec3fNormalize(Vec3f *vec) {
  float mag = vec3fMagnitude(vec);
  vec->x /= mag;
  vec->y /= mag;
  vec->z /=mag;
}

float vec3fDotProduct(Vec3f *vec1, Vec3f *vec2) {
  float result;
  result += vec1->x * vec2->x;
  result += vec1->y * vec2->y;
  result += vec1->z * vec2->z;
  return result;
}