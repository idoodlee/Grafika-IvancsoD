#include "scene.h"

#include <math.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"


#include <GL/gl.h>

void init_scene(Scene* scene)
{
 
    

    scene->sky_texture = load_texture("assets/textures/sky.jpg");

    scene->table_texture = load_texture("assets/textures/table.png");

    scene->help_image = load_texture("assets/textures/help.jpg");
    load_model(&(scene->plate), "assets/models/plate.obj");

     load_model(&(scene->fank), "assets/models/f.obj");
    scene->texture_fank = load_texture("assets/textures/fank.jpg");
    load_model(&(scene->maz), "assets/models/m.obj");
    scene->texture_maz = load_texture("assets/textures/maz.jpg");

   
    load_model(&(scene->fank2), "assets/models/f.obj");
    scene->texture_fank = load_texture("assets/textures/fank.jpg");
    load_model(&(scene->maz2), "assets/models/m.obj");
    scene->texture_maz2 = load_texture("assets/textures/maz2.jpg");

    load_model(&(scene->fank3), "assets/models/f.obj");
    scene->texture_fank = load_texture("assets/textures/fank.jpg");
    load_model(&(scene->maz3), "assets/models/m.obj");
    scene->texture_maz3 = load_texture("assets/textures/maz3.jpg");

    load_model(&(scene->talp), "assets/models/talp.obj");
    scene->texture_fa = load_texture("assets/textures/fa.png");

    load_model(&(scene->lap), "assets/models/lap.obj");
    scene->texture_f = load_texture("assets/textures/f.png");

    scene->texture_p = load_texture("assets/textures/p.png");

    
    load_model(&(scene->cake1), "assets/models/cake.obj");
    load_model(&(scene->cake2), "assets/models/cake.obj") ; 
    load_model(&(scene->cake3), "assets/models/cake.obj");

    scene->texture_kakao = load_texture("assets/textures/kakao.jpg");
    scene->texture_sima = load_texture("assets/textures/sima.jpg");
    scene->texture_velvet = load_texture("assets/textures/velvet.jpg");

    

    load_model(&(scene->cream1), "assets/models/cake.obj");
    load_model(&(scene->cream2), "assets/models/cake.obj");

    scene->texture_eper = load_texture("assets/textures/eper.jpg");
    scene->texture_csoki = load_texture("assets/textures/csoki.jpg");
    scene->texture_vanilia = load_texture("assets/textures/vanilia.jpg");

    scene->texture_cream1 = scene->texture_csoki;
    scene->texture_cream1 = scene->texture_eper;
    scene->texture_cream1 = scene->texture_vanilia;

    scene->texture_cream2 = scene->texture_csoki;
    scene->texture_cream2 = scene->texture_eper;
    scene->texture_cream2 = scene->texture_vanilia;


    scene->texture_cake1 = scene->texture_kakao;
    scene->texture_cake1 = scene->texture_sima;
    scene->texture_cake1 = scene->texture_velvet;
   
    scene->texture_cake2 = scene->texture_kakao;
    scene->texture_cake2 = scene->texture_sima;
    scene->texture_cake2 = scene->texture_velvet;
   
    scene->texture_cake3 = scene->texture_kakao;
    scene->texture_cake3 = scene->texture_sima;
    scene->texture_cake3 = scene->texture_velvet;





    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 1.0;
    scene->light_intensity = 1.0f;

 

    scene->display_help = false;
}

void set_lighting(const Scene* scene)
{
    float intensity = scene->light_intensity;
    float ambient_light[] = { 0.4f * intensity, 0.4f * intensity, 0.4f * intensity, 1.0f };
    float diffuse_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}



void set_material(const Material* material, float alpha)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue,
        alpha
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue,
        alpha
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue,
        alpha
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void help(GLuint Help_menu) {
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);  // Elmentjük az állapotokat

    glDisable(GL_DEPTH_TEST);     // Depth teszt kikapcsolása
    glDisable(GL_LIGHTING);       // Világítás kikapcsolása
    glEnable(GL_TEXTURE_2D);      // Textúrázás bekapcsolása
    glEnable(GL_BLEND);           // Blendelés bekapcsolása
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Átlátszóság kezelése

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);  // Ortográfikus nézet beállítása

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, Help_menu);
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);  // Fehér szín, teljes átlátszatlanság
    glTexCoord2f(0, 0); glVertex2f(-1,  1);
    glTexCoord2f(1, 0); glVertex2f( 1,  1);
    glTexCoord2f(1, 1); glVertex2f( 1, -1);
    glTexCoord2f(0, 1); glVertex2f(-1, -1);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopAttrib();  // Visszaállítjuk a mentett állapotokat
}


void render_scene(const Scene* scene)
{
    set_material(&(scene->material), 1.0f);
    set_lighting(scene);

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    render_floor(scene->table_texture);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    render_skybox(scene->sky_texture);
    glPopMatrix();

//tányér
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(10.0f, 10.0f, 10.0f);
    glTranslatef(1, 0, 0.004);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_f);
    draw_model(&(scene->plate));
    glPopMatrix();
//fánk1
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, 0, 1);
    glRotatef(0, 0, 0, 0);
    glScalef(3.0f, 3.0f, 3.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_fank);
    draw_model(&(scene->fank));
    glPopMatrix();

//fánkmáz 1
 glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, 0, 1);
    glRotatef(0, 0, 0, 0);
    glScalef(3.0f, 3.0f, 3.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_maz);
    draw_model(&(scene->maz));
    glPopMatrix();

//fánk 2
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, 0, 2.5);
    glRotatef(0, 0, 0, 0);
    glScalef(3.0f, 3.0f, 3.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_fank);
    draw_model(&(scene->fank2));
    glPopMatrix();
//fánkmáz 2
 glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, 0, 2.5);
    glRotatef(0, 0, 0, 0);
    glScalef(3.0f, 3.0f, 3.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_maz2);
    draw_model(&(scene->maz2));
    glPopMatrix();

 //fánk3
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, -3.0, 0.6);
    glRotatef(0, 0, 0, 0);
    glScalef(2.0f, 2.0f, 2.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_fank);
    draw_model(&(scene->fank3));
    glPopMatrix();

//fánkmáz 3
 glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, -3, 0.6);
    glRotatef(0, 0, 0, 0);
    glScalef(2.0f, 2.0f, 2.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_maz3);
    draw_model(&(scene->maz3));
    glPopMatrix();

//Tortaállvány talpa
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(3, 11, 0.004);
    glRotatef(90, 1, 0, 0);
    glScalef(1.5f, 1.5f, 1.5f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_fa);
    draw_model(&(scene->talp));
    glPopMatrix();

 //Tortaállvány lapja   
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(11.0f, 11.0f, 11.0f);
    glTranslatef(0.28, 1, 0.28);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_p);
    draw_model(&(scene->lap));
    glPopMatrix();

//Piskóta alsó
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(11.0f, 11.0f, 11.0f);
    glTranslatef(0.28, 1, 0.26);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_cake1);
    draw_model(&(scene->cake1));
    glPopMatrix();

 //Krém alsó
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(11.0f, 11.0f, 11.0f);
    glTranslatef(0.28, 1, 0.3);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_cream1);
    draw_model(&(scene->cream1));
    glPopMatrix();

//Piskóta középső
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(11.0f, 11.0f, 11.0f);
    glTranslatef(0.28, 1, 0.34);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_cake2);
    draw_model(&(scene->cake2));
    glPopMatrix();

//Krém felső
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(11.0f, 11.0f, 11.0f);
    glTranslatef(0.28, 1, 0.38);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_cream2);
    draw_model(&(scene->cream2));
    glPopMatrix();

//Piskóta felső
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(11.0f, 11.0f, 11.0f);
    glTranslatef(0.28, 1, 0.42);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_cake3);
    draw_model(&(scene->cake3));
    glPopMatrix();


    

    if (scene->display_help)
    {
        help(scene->help_image);
    }

    
}

void render_floor(GLuint texture_name)
{
    float size = 50.0f;
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glRotatef(-90, 1, 0, 0);  

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);  // Általában a textúra színét a textúra maga határozza meg, ezért fehérre állítjuk az alapszínt

    glTexCoord2f(0, 0); glVertex3f(-size, 0, -size); // Bal alsó sarok
    glTexCoord2f(1, 0); glVertex3f(size, 0, -size);  // Jobb alsó sarok
    glTexCoord2f(1, 1); glVertex3f(size, 0, size);   // Jobb felső sarok
    glTexCoord2f(0, 1); glVertex3f(-size, 0, size);  // Bal felső sarok

    glEnd();
    
    glPopMatrix();
}




void render_skybox(GLuint texture_name) {
    glPushMatrix();
    glDepthMask(GL_FALSE);  // Disable depth writing

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glBegin(GL_QUADS);

    // jobb oldal
    glTexCoord2f(1, 1); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(0, 1); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(0, 0); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1, 0); glVertex3f(-50.0f, -50.0f, 50.0f);


    // bal oldal
    glTexCoord2f(1, 1); glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(0, 1); glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0, 0); glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(1, 0); glVertex3f(-50.0f, 50.0f, 50.0f);

    //  Felső oldal
    glTexCoord2f(0, 0); glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1, 0); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1, 1); glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0, 1); glVertex3f(-50.0f, 50.0f, 50.0f);

    // AlSó oldal
   glTexCoord2f(0, 0); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1, 0); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1, 1); glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(0, 1); glVertex3f(50.0f, 50.0f, -50.0f);

    // Hátsó oldal
    glTexCoord2f(0, 1); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(0, 0); glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1, 0); glVertex3f(-50.0f, 50.0f, 50.0f);
    glTexCoord2f(1, 1); glVertex3f(-50.0f, 50.0f, -50.0f);

    // Első oldal
    glTexCoord2f(1, 0); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1, 1); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(0, 1); glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0, 0); glVertex3f(50.0f, 50.0f, 50.0f);

    glEnd();

    glDepthMask(GL_TRUE);  // Re-enable depth writing
    glPopMatrix();
}

