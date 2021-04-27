/*
[SZÁMÍTÓGÉPI GRAFIKA BEADANDÓ FELADAT]
[----------LOW-BUDGET SIMCITY-------]
[-------------Kozma János-----------]
[---------------SVOXGH--------------]
*/

#include "callbacks.h"
#include "init.h"
#include "model.h"
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(1280, 720);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Low-budget Simcity - Kozma Janos - SVOXGH");

    init();

    glutMainLoop();

    return 0;
}

void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialFunc);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    glutIdleFunc(idle);
}
