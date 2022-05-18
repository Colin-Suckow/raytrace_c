#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct {
  float x;
  float y;
  float z;
} Vec3f;

typedef struct {
  Vec3f origin;
  Vec3f dir;
} Ray;

float vec3fMagnitude(const Vec3f *vec);
void vec3fNormalize(Vec3f *vec);
float vec3fDotProduct(const Vec3f *vec1, const Vec3f *vec2);
Vec3f vec3fSubtract(const Vec3f *vec1, const Vec3f *vec2);

bool solveQuadratic(const float a, const float b, const float c, float *x0, float *x1);

#endif