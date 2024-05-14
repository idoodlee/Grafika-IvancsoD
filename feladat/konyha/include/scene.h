#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{   

    Material material;
    Model plate;
    Model fank;
    Model maz;
    Model fank2;
    Model maz2;
    Model fank3;
    Model maz3;
    Model talp;
    Model lap;
    Model cake1;
    Model cake2;
    Model cake3;
    Model cream1;
    Model cream2;
    
    
    GLuint table_texture;
    GLuint sky_texture;
    GLuint texture_fank;
    GLuint texture_maz, texture_maz2, texture_maz3;
    GLuint texture_fa;
    GLuint texture_f;
    GLuint texture_p;

    GLuint texture_kakao, texture_sima, texture_velvet;
    GLuint texture_cake1, texture_cake2, texture_cake3;

    GLuint texture_csoki, texture_eper, texture_vanilia;
    GLuint texture_cream1, texture_cream2;

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