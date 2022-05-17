#ifndef VECTOR_H
#define VECTOR_H


typedef struct {
  float x;
  float y;
  float z;
} Vec3f;

float vec3fMagnitude(Vec3f *vec);
void vec3fNormalize(Vec3f *vec);
float vec3fDotProduct(Vec3f *vec1, Vec3f *vec2);

#endif