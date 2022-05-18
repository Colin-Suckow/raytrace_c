#include <stdlib.h>
#include "scene.h"

void sceneCleanup(Scene *scene) {
  for (int i = 0; i < scene->objectCount; i++) {
    free(scene->objects[i].object);
  }
  free(scene->objects);
}