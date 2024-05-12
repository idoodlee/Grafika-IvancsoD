#include "scene.h"
#include "math.h"

#include <GL/glut.h>

void init_scene(Scene* scene)
{
	scene->pot_rotation=0.0;
}

void draw_scene(const Scene* scene)
{
	int i, k;

    draw_origin();
	
	
	for(i=0;i<10;++i){
		for(k=0;k<10;++k){
		glPushMatrix();
		glTranslatef(i, k, 0);

		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(1, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 1, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 1);
		glEnd();
		glPopMatrix();

		}
	}
	
	glPushMatrix();
	glRotatef(scene->pot_rotation, 1, 0, 0);
	glColor3f(sin(scene->pot_rotation / 10), 0, 0);
	glutWireTeapot(sin(scene->pot_rotation/10));
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
void update_scene(Scene* scene, double time)
{
	scene->pot_rotation += 5.0 * time;
}