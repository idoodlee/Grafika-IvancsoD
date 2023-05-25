#include "scene.h"
#include <time.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>

void init_scene(Scene* scene)
{

	load_model(&(scene->sun), "assets/models/sun.obj");
	scene->sun_texture = load_texture("assets/textures/sun_texture.jpg");

    load_model(&(scene->mercury), "assets/models/mercury.obj");
	scene->mercury_texture = load_texture("assets/textures/mercury_texture.jpg");

    load_model(&(scene->venus), "assets/models/venus.obj");
	scene->venus_texture = load_texture("assets/textures/venus_texture.jpg");

    load_model(&(scene->earth), "assets/models/earth.obj");
	scene->earth_texture = load_texture("assets/textures/earth_texture.jpg");

    load_model(&(scene->mars), "assets/models/mars.obj");
	scene->mars_texture = load_texture("assets/textures/mars_texture.jpg");

    load_model(&(scene->jupiter), "assets/models/jupiter.obj");
	scene->jupiter_texture = load_texture("assets/textures/jupiter_texture.jpg");

    load_model(&(scene->saturn), "assets/models/saturn.obj");
	scene->saturn_texture = load_texture("assets/textures/saturn_texture.jpg");

    load_model(&(scene->uranus), "assets/models/uranus.obj");
	scene->uranus_texture = load_texture("assets/textures/uranus_texture.jpg");

    load_model(&(scene->neptune), "assets/models/neptune.obj");
	scene->neptune_texture = load_texture("assets/textures/neptune_texture.jpg");

    load_model(&(scene->pluto), "assets/models/pluto.obj");
	scene->pluto_texture = load_texture("assets/textures/pluto_texture.jpg");

    scene->skybox_texture = load_texture("assets/textures/skybox_texture.jpg");

    load_model(&(scene->ground), "assets/models/ground.obj");
	scene->ground_texture = load_texture("assets/textures/skybox_texture.jpg");

    scene->Help_menu = load_texture("assets/textures/help_texture.jpg");

	scene->motion_up = true;
	
    scene->material.ambient.red = 1.0f;
    scene->material.ambient.green = 1.0f;
    scene->material.ambient.blue = 1.0f;

    scene->material.diffuse.red = 1.0f;
    scene->material.diffuse.green = 1.0f;
    scene->material.diffuse.blue = 1.0f;

    scene->material.specular.red = 1.0f;
    scene->material.specular.green = 1.0f;
    scene->material.specular.blue = 1.0f;
    scene->material.shininess = 1.0f;
	
	scene->angle = 0;
	scene->Help_visible = false;

}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}


void load_skybox(Scene scene) {

    glBindTexture(GL_TEXTURE_2D, scene.skybox_texture);

    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;
    int n_slices, n_stacks;
    double radius;
    int i, k;
    n_slices = 15;
    n_stacks = 15;
    radius = 70;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double) i / n_stacks;
        v2 = (double) (i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double) k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1) - 0.25;
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2) - 0.25;
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();

}

void load_sun(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
    glTranslated(0, 20, 4);
    glBindTexture(GL_TEXTURE_2D, scene.sun_texture);
    draw_model(&(scene.sun));
	
    glPopMatrix();
}
void load_mercury(Scene scene) {

    glPushMatrix();
    glScaled(0.8, 0.8, 0.8);
    glTranslated(0, 17, 4);
    glBindTexture(GL_TEXTURE_2D, scene.mercury_texture);
    draw_model(&(scene.mercury));
	
    glPopMatrix();
}
void load_venus(Scene scene) {


    glPushMatrix();
    glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 13, 4);
    glBindTexture(GL_TEXTURE_2D, scene.venus_texture);
    draw_model(&(scene.venus));
	
    glPopMatrix();
}
void load_earth(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
    glTranslated(0, 10, 4);
    glBindTexture(GL_TEXTURE_2D, scene.earth_texture);
    draw_model(&(scene.earth));
	
    glPopMatrix();
}
void load_mars(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 7, 4);
    glBindTexture(GL_TEXTURE_2D, scene.mars_texture);
    draw_model(&(scene.mars));
	
    glPopMatrix();
}
void load_jupiter(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 5, 4);
    glBindTexture(GL_TEXTURE_2D, scene.jupiter_texture);
    draw_model(&(scene.jupiter));
	
    glPopMatrix();
}
void load_saturn(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 2, 4);
    glBindTexture(GL_TEXTURE_2D, scene.saturn_texture);
    draw_model(&(scene.saturn));
	
    glPopMatrix();
}
void load_uranus(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 1, 4);
    glBindTexture(GL_TEXTURE_2D, scene.uranus_texture);
    draw_model(&(scene.uranus));
	
    glPopMatrix();
}
void load_neptune(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 0.5, 4);
    glBindTexture(GL_TEXTURE_2D, scene.neptune_texture);
    draw_model(&(scene.neptune));
	
    glPopMatrix();
}
void load_pluto(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
	glTranslated(0, 0, 4);
    glBindTexture(GL_TEXTURE_2D, scene.pluto_texture);
    draw_model(&(scene.pluto));
	
    glPopMatrix();
}

void load_ground(Scene scene) {
	
    glPushMatrix();
	glTranslated(0, 0, -0.4);
    glBindTexture(GL_TEXTURE_2D, scene.skybox_texture);
	glTranslated(0, 0, -0.4);
    draw_model(&(scene.ground));
    glPopMatrix();
}

void Help(GLuint Help_menu) {
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, Help_menu);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3d(-2, 1.5, -3);
        glTexCoord2f(1, 0);
        glVertex3d(2, 1.5, -3);
        glTexCoord2f(1, 1);
        glVertex3d(2, -1.5, -3);
        glTexCoord2f(0, 1);
        glVertex3d(-2, -1.5, -3);
        glEnd();


        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
}

void load_glass(Scene scene){
    glBlendFunc(GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glBegin(GL_QUADS);

    glColor4f(0.0, 0.0, 0.0, 10.0);
    glNormal3f(1.0, 1.0, 1.0);

    glVertex3f(-20.0, -20.0, 2.0);
    glVertex3f(-20.0, 20.0, 2.0);
    glVertex3f(20.0, 20.0, 2.0);
    glVertex3f(20.0, -20.0, 2.0);

    glVertex3f(2.6, 2.6, 0.0);
    glVertex3f(2.6, 2.6, 5.0);

    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}

void update_scene(Scene* scene, double time)
{
	scene->angle += 50 * time;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();

    load_sun(*scene);
    load_mercury(*scene);
    load_venus(*scene);
    load_earth(*scene);
    load_mars(*scene);
    load_jupiter(*scene);
    load_saturn(*scene);
    load_uranus(*scene);
    load_neptune(*scene);
    load_pluto(*scene);
    load_skybox(*scene);
    load_ground(*scene);
    load_glass(*scene);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}