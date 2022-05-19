#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "vector.h"
#include "image.h"

typedef struct {
  Vec3f sunDir;
  float globalLightIntensity;
} EnvironmentSettings;

typedef struct {
  bool (*intersect)(Ray *ray, void *objectData, float *t);
  Color (*paint)(Ray *ray, void *objectData, float t, const EnvironmentSettings *env);
  void *object;
} SceneObject;



typedef struct {
  int objectCount;
  SceneObject *objects;
  EnvironmentSettings envSettings;
} Scene;

void sceneCleanup(Scene *scene);

#endif