#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sphere.h"
#include "scene.h"

bool intersect(Ray *ray, void *objectData, float *t) {
  SphereSceneObject sphere = *(SphereSceneObject *) objectData;
  
  Vec3f L = vec3fSubtract(&ray->origin, &sphere.pos);
  float a = vec3fDotProduct(&ray->dir, &ray->dir);
  float b = 2.0 * vec3fDotProduct(&ray->dir, &L);
  float c = vec3fDotProduct(&L, &L) - (sphere.radius * sphere.radius);
  float t0, t1;
  
  if (!solveQuadratic(a, b, c, &t0, &t1)) return false;
  
  if (t0 < 0) {
    t0 = t1;
    if (t0 < 0) return false;
  }
  *t = t0;
  return true;
}

SceneObject sphereInit(Vec3f pos, float radius) {
  SceneObject result;
  SphereSceneObject *data = (SphereSceneObject *) malloc(sizeof(SphereSceneObject));

  data->pos = pos;
  data->radius = radius;

  result.intersect = &intersect;
  result.object = (void *) data;
  return result;
}