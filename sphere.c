#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "sphere.h"
#include "scene.h"
#include "image.h"

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

Color paint(Ray *ray, void *objectData, float t, const EnvironmentSettings *env) {
  SphereSceneObject sphere = *(SphereSceneObject *) objectData;
  
  Vec3f Phit, Nhit;
  float lat, lon;

  Vec3f mult = vec3fMultf(&ray->dir, t);
  Phit = vec3fAdd(&ray->origin, &mult);
  Nhit = vec3fSubtract(&Phit, &sphere.pos);
  
  lat = (1 + atan2f(Nhit.z, Nhit.x) / 3.14159) * 0.5;
  lon = acosf(Nhit.y) / 3.14159;

  float lightSim = vec3fDotProduct(&Nhit, &env->sunDir) / vec3fMagnitude(&env->sunDir);
  if (lightSim < 0) {
    lightSim = 0;
  }

  float base = 0;
  if ((int) (lon * 100.) % 10 <= 5 || (int) (lat * 100. + 5) % 10 <= 5) {
    base = 0.2;
  } else {
    base = 0.4;
  }

  base *= lightSim + env->globalLightIntensity;

  if (base > 1.0) {
    base = 1.0;
  }

  if (base < 0.0) {
    base = 0.0;
  }

  return (Color) {255. * base, 255. * base, 255. * base};
} 

SceneObject sphereInit(Vec3f pos, float radius) {
  SceneObject result;
  SphereSceneObject *data = (SphereSceneObject *) malloc(sizeof(SphereSceneObject));

  data->pos = pos;
  data->radius = radius;

  result.intersect = &intersect;
  result.paint = &paint;
  result.object = (void *) data;
  return result;
}