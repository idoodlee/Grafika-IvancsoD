#include "camera.h"
#include "scene.h"
#include <GL/gl.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

     camera->is_preview_visible = false;
    camera->locked = false;
}

void update_camera(Camera* camera, double time, double wheel_rotation, vec3 wheel_position)
{
    if (camera->locked) {
        double angle = degree_to_radian(wheel_rotation);

        double radius = 2.0; // A sugár, ami a kamera távolságát jelöli a forgásponttól

        // Kamera pozíciójának kiszámítása
        camera->position.x = wheel_position.x + radius * cos(angle);
        camera->position.y = wheel_position.y + radius * sin(angle) +1.0;
        camera->position.z = wheel_position.z + 2.3; // Növeljük a Z koordinátát, hogy magasabban legyen

        // Kamera irányának kiszámítása a forgáspont felé
        double dx = wheel_position.x - camera->position.x;
        double dy = wheel_position.y - camera->position.y;

        // Kamera nézeti szögeinek beállítása
        camera->rotation.y = atan2(dy, dx) * 180.0 / M_PI + 180;
        camera->rotation.x = -35;
    } else {
        // Normál kamera mozgatás, ha a kamera nincs zárolva
        double angleY = degree_to_radian(camera->rotation.y);
        camera->position.x += camera->speed.x * cos(angleY) * time;
        camera->position.y += camera->speed.x * sin(angleY) * time;
    }
}






void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}
void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
