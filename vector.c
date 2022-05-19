#include <math.h>
#include <stdbool.h>
#include "vector.h"

float vec3fMagnitude(const Vec3f *vec) {
  return sqrtf((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
}

void vec3fNormalize(Vec3f *vec) {
  float mag = vec3fMagnitude(vec);
  vec->x /= mag;
  vec->y /= mag;
  vec->z /=mag;
}

float vec3fDotProduct(const Vec3f *vec1, const Vec3f *vec2) {
  float result = 0.0;
  result += vec1->x * vec2->x;
  result += vec1->y * vec2->y;
  result += vec1->z * vec2->z;
  return result;
}

Vec3f vec3fAdd(const Vec3f *vec1, const Vec3f *vec2) {
  Vec3f result;
  result.x = vec1->x + vec2->x;
  result.y = vec1->y + vec2->y;
  result.z = vec1->z + vec2->z;
  return result;
}


Vec3f vec3fSubtract(const Vec3f *vec1, const Vec3f *vec2) {
  Vec3f result;
  result.x = vec1->x - vec2->x;
  result.y = vec1->y - vec2->y;
  result.z = vec1->z - vec2->z;
  return result;
}

Vec3f vec3fMultf(const Vec3f *vec, float mult) {
  Vec3f result;
  result.x = vec->x * mult;
  result.y = vec->y * mult;
  result.z = vec->z * mult;
  return result;
}

bool solveQuadratic(float a, float b, float c, float *x0, float *x1) {
    float discr = b * b - 4. * a * c;
    if (discr < 0) return false; 
    else if (discr == 0) {
      *x0 = *x1 = - 0.5 * b / a; 
    } else { 
        float q = (b > 0) ? -0.5 * (b + sqrtf(discr)) : -0.5 * (b - sqrtf(discr)); 
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
