#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "cube.obj");
    scene->texture_id = load_texture("cube.png"); 

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    /*Ruby
    float[] mat_ambient ={ 0.1745f, 0.01175f, 0.01175f, 0.55f };
    float[] mat_diffuse ={0.61424f, 0.04136f, 0.04136f, 0.55f };
    float[] mat_specular ={0.727811f, 0.626959f, 0.626959f, 0.55f };
    float shine =76.8f ;*/

    scene->material.ambient.red = 0.1745f;
    scene->material.ambient.green = 0.01175f;
    scene->material.ambient.blue = 0.01175f;

    scene->material.diffuse.red = 0.61424f;
    scene->material.diffuse.green = 0.04136f;
    scene->material.diffuse.blue = 0.04136f;

    scene->material.specular.red = 0.727811f;
    scene->material.specular.green = 0.626959f;
    scene->material.specular.blue = 0.626959f;

    scene->material.shininess = 76.8f;
}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 5.0f, 2.0f, 2.0f, 1.0f };

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

void draw_scene(const Scene* scene)
{
    int i;
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    glPushMatrix();
    for(i=0; i<10; ++i){
        glTranslatef(2, 0, 0);
        glutSolidSphere(1, 30, 30);
    }
        glPopMatrix();

        glPushMatrix();
        glTranslatef(5, 2, 2);
        draw_model(&(scene->cube));
        glPopMatrix();
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
