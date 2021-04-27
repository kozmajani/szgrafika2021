/*
[SZÁMÍTÓGÉPI GRAFIKA BEADANDÓ FELADAT]
[----------LOW-BUDGET SIMCITY-------]
[-------------Kozma János-----------]
[---------------SVOXGH--------------]
*/

#include "GL/glut.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "draw.h"
#include "model.h"
#include "callbacks.h"

double citySize = 200;

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_teapot_for_light(){
    glPushMatrix();
        glTranslatef(120, 15, 120);
        glScalef(12, 12, 12);
        glutSolidTeapot(1.0);
    glPopMatrix();
}

void draw_content(World* world)
{
	City drawCity = world -> city;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_walls(drawCity);
		draw_ground(drawCity);
	glPopMatrix();


	//house1 - fa mintás ház
	glPushMatrix();
		glTranslatef(world->house1.position.x, world->house1.position.y, world->house1.position.z);
        glRotatef(0, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world->house1.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->house1.texture);
		glScalef(0.6f, 0.6f, 0.6f);

		draw_model(&world->house1.model);
    glPopMatrix();

    //house2 - tégla mintás ház
	glPushMatrix();
		glTranslatef(world->house2.position.x, world->house2.position.y, world->house2.position.z);
        glRotatef(0, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->house2.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->house2.texture);
		glScalef(0.02f,0.02f, 0.02f);

		draw_model(&world->house2.model);
    glPopMatrix();

    //house3 - kék csempe mintás ház
    glPushMatrix();
        glTranslatef(world->skyscraper.position.x, world->skyscraper.position.y, world->skyscraper.position.z);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->skyscraper.material_ambient);

        glBindTexture(GL_TEXTURE_2D, world->skyscraper.texture);
        glScalef(0.032f, 0.032f, 0.032f);

        draw_model(&world->skyscraper.model);
    glPopMatrix();
	
	    //border buildings - szürke, fekete pöttyös házak
		glPushMatrix();
			glTranslatef(world->border_b1.position.x, world->border_b1.position.y, world->border_b1.position.z);
			glRotatef(0, 0.0f, 0.0f, 0.0f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->border_b1.material_ambient);

			glBindTexture(GL_TEXTURE_2D, world->border_b1.texture);
			glScalef(0.85f, 0.85f, 0.85f);

			draw_model(&world->border_b1.model);
			
		glPopMatrix();
			
		glPushMatrix();
			glTranslatef(world->border_b2.position.x, world->border_b2.position.y, world->border_b2.position.z);
			glRotatef(90, 0.0f, 90.0f, 0.0f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->border_b2.material_ambient);

			glBindTexture(GL_TEXTURE_2D, world->border_b2.texture);
			glScalef(1.0f, 1.0f, 1.0f);

			draw_model(&world->border_b2.model);
			
		glPopMatrix();
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_default);
}

void draw_ground(City city) { //ismétlődő textúrás aljzat
	glBindTexture(GL_TEXTURE_2D, city.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -citySize; x < citySize; x += 50) {
		for (z = -citySize; z < citySize; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}
void draw_walls(City city) { //város körüli skybox
	glBindTexture(GL_TEXTURE_2D, city.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-citySize, 0, -citySize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-citySize, citySize, -citySize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-citySize, citySize, citySize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-citySize, 0, citySize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, city.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(citySize, 0, citySize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(citySize, citySize, citySize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(citySize, citySize, -citySize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(citySize, 0, -citySize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, city.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-citySize, 0, -citySize);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(citySize, 0, -citySize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(citySize, citySize, -citySize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-citySize, citySize, -citySize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, city.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-citySize, 0, citySize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-citySize, citySize, citySize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(citySize, citySize, citySize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(citySize, 0, citySize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, city.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(citySize, citySize, citySize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(citySize, citySize, -citySize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-citySize, citySize, -citySize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-citySize, citySize, citySize);
	glEnd();
}

void draw_triangles(const struct Model* model)
{
	int i, k;
	int vertex_index, texture_index, normal_index;
	double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_TRIANGLES);

	for (i = 0; i < model->n_triangles; ++i) {
		for (k = 0; k < 3; ++k) {
			normal_index = model->triangles[i].points[k].normal_index;
			normal_x = model->normals[normal_index].x;
			normal_y = model->normals[normal_index].y;
			normal_z = model->normals[normal_index].z;
			glNormal3d(normal_x, normal_y, normal_z);

			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
            switch(k){
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1*z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
			glVertex3d(x, y, z);

		}
	}

	glEnd();
}


void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

	glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_normals(const struct Model* model, double length)
{
	int i;
	double x1, y1, z1, x2, y2, z2;

	glColor3f(0, 0, 1);

	glBegin(GL_LINES);

	for (i = 0; i < model->n_vertices; ++i) {
		x1 = model->vertices[i].x;
		y1 = model->vertices[i].y;
		z1 = model->vertices[i].z;
		x2 = x1 + model->normals[i].x * length;
		y2 = y1 + model->normals[i].y * length;
		z2 = z1 + model->normals[i].z * length;
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y2, z2);
	}
	glEnd();
}

void draw_model(const struct Model* model)
{
	draw_triangles(model);
	draw_quads(model);
}

void draw_help(int texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
