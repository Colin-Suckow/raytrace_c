#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "vector.h"

typedef struct {
  bool (*intersect)(Ray *ray, void *objectData, float *t);
  void *object;
} SceneObject;

typedef struct {
  int objectCount;
  SceneObject *objects;
} Scene;

void sceneCleanup(Scene *scene);

#endif