#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "math.h"


typedef struct Scene
{
    // NOTE: Place for model structures and texture ids.
	float pot_rotation;
} Scene;

/**
 * Initialize the scene.
 */
void init_scene(Scene* scene);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void update_scene(Scene* scene, double time);

#endif /* SCENE_H */

