#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{   

   
    Model plate;
    Model fank;
    Material material;
    Model maz;
   
    GLuint table_texture;
    GLuint sky_texture;
    GLuint texture_fank;
    GLuint texture_maz;

    GLuint help_image;

    bool display_help;
    float light_intensity;
    vec3 wheel_position; 
    float wheel_rotation;

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
void set_material(const Material* material, float alpha);

void update_scene(Scene* scene, double time);
/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

void help(GLuint Help_menu);

void render_floor(GLuint texture_name);

void draw_laser_beam();

void render_skybox(GLuint texture_name);

#endif /* SCENE_H */