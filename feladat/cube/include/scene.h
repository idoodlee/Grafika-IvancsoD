#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>


typedef struct Scene
{
    Model sun;
	Model mercury;
	Model ground;
	Model venus;
	Model earth;
	Model mars;
	Model jupiter;
	Model saturn;
	Model uranus;
	Model neptune;
	Model pluto;

    Material material;

	GLuint ground_texture;
	GLuint skybox_texture;
	GLuint sun_texture;
	GLuint mercury_texture;
	GLuint venus_texture;
	GLuint earth_texture;
	GLuint mars_texture;
	GLuint jupiter_texture;
	GLuint saturn_texture;
	GLuint uranus_texture;
	GLuint neptune_texture;
	GLuint pluto_texture;

	GLuint Help_menu;
	
	double angle;
	double rotate;
	bool Help_visible;
	bool motion_up;
} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Load the skybox.
 */
void load_skybox(Scene scene);

#endif /* SCENE_H */
