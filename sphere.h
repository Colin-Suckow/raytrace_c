#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "scene.h"

typedef struct {
  Vec3f pos;
  float radius;
} SphereSceneObject;

SceneObject sphereInit(Vec3f pos, float radius);

#endif