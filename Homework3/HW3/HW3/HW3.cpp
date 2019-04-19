// HW1.cpp : 定義主控台應用程式的進入點。
//
/*********************************
4104056004 李家駿 第三次作業 4/17
The Main function
Rotating and camera moving.
*********************************/
#include "stdafx.h"
#include "rendering/draw_all.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
static int draw_type=MY_DRAW_ARRAYS;
static float camera_x = 0,camera_y=0,camera_z=3;
static float angle_x = 0, angle_y = 0, angle_z = 0;
static int angle_logo = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-NCHU_WIDTH/2 , NCHU_WIDTH / 2, -NCHU_HEIGHT / 2, NCHU_HEIGHT / 2, 1, 10);
	//glShadeModel(GL_FLAT);
	glFlush();
	glutSwapBuffers();
	srand(time(NULL));
	//glFrustum(0, 400, 0, 200, 1, 50);
	camera_x = 0;
	camera_y = 0;
	camera_z = 3;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	angle_logo = 0;
}
void logo_idle_display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glPushMatrix();
		/*Rotate*/
		glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
		glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
		glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

		/*Move center to (0,0,0)*/
		glTranslatef(-width / 2, -height / 2, 0);

		/*Move logo back*/
		glTranslatef(701, (height - 93), 0);

		/*Self rotating*/
		angle_logo += 10;
		glRotatef((angle_logo) % 360, 0, 0, 1);
		
		/*Move logo center to (0,0,0)*/
		glTranslatef(-701,-(height - 93), 0);

		/*Automatically change color */
		logo_square.color[0] = (float)rand()/RAND_MAX;
		logo_square.color[1] = (float)rand() / RAND_MAX;
		logo_square.color[2] = (float)rand() / RAND_MAX;
		logo_circle.color[0] = (float)rand() / RAND_MAX;
		logo_circle.color[1] = (float)rand() / RAND_MAX;
		logo_circle.color[2] = (float)rand() / RAND_MAX;

		/*Draw the mark part*/
		render_logo(draw_type);

	glPopMatrix();
	glutSwapBuffers();

	glutPostRedisplay();
}
void display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glPushMatrix();
		/*Rotate*/
		glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
		glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
		glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

		/*Move center to (0,0,0)*/
		glTranslatef(-width/2, -height/2, 0);

		/* clear all pixels  */
		glClear(GL_COLOR_BUFFER_BIT);

		/*Draw the chinese part*/
		render_chinese(draw_type);

		/*Draw the mark part*/
		//render_logo(draw_type);

		/*Draw the english part*/
		render_english(draw_type);
	glPopMatrix();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	//glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w>h)
		glFrustum((-NCHU_WIDTH / 2)*(GLfloat)h / (GLfloat)w, (NCHU_WIDTH / 2)*(GLfloat)h / (GLfloat)w, (-NCHU_HEIGHT / 2)*(GLfloat)h / (GLfloat)w, (NCHU_HEIGHT /2)*(GLfloat)h / (GLfloat)w, 1, 10);

	else
		glFrustum((-NCHU_WIDTH / 2)*(GLfloat)w / (GLfloat)h, (NCHU_WIDTH / 2)*(GLfloat)w / (GLfloat)h, (-NCHU_HEIGHT / 2)*(GLfloat)w / (GLfloat)h, (NCHU_HEIGHT / 2)*(GLfloat)w / (GLfloat)h, 1, 10);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		/*Change rendering method.*/
		case '1':
			init();
			draw_type = MY_DRAW_ARRAYS;
			break;
		case '2':
			init();
			draw_type = MY_DRAW_ELEMENTS;
			break;
		case '3':
			init();
			draw_type = MY_MULTI_DRAW_ARRAYS;
			break;
		case '4':
			init();
			draw_type = MY_MULTI_DRAW_ELEMENTS;
			break;

		/*Move*/
		case 'W':
			/*Move forward.*/
			camera_z -= 0.1;
			break;
		case 'w':
			camera_z -= 0.1;
			break;
		case 'S':
			/*Move backward.*/
			camera_z += 0.1;
			break;
		case 's':
			camera_z += 0.1;
			break;
		case 'A':
			/*Move left.*/
			camera_x -= 5;
			break;
		case 'a':
			camera_x -= 5;
			break;
		case 'D':
			/*Move forward.*/
			camera_x += 5;
			break;
		case 'd':
			camera_x += 5;
			break;
		/*Other*/
		case '0':
			init();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)	//Rotate by x-axis while press left button of mouse.
				angle_x = ((int)angle_x + 30) % 360;
			else
				;
			break;
		case GLUT_MIDDLE_BUTTON:
			if (state == GLUT_DOWN)	//Rotate by z-axis while press left button of mouse.
				angle_z = ((int)angle_z + 10) % 360;
			else
				;
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)	//Rotate by y-axis while press left button of mouse.
				angle_y = ((int)angle_y + 30) % 360;
			else
				;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
/*
* Declare initial window size, position, and display mode
* (single buffer and RGBA).  Open window with "hello"
* in its title bar.  Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(NCHU_WIDTH, NCHU_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework3");
	init();
	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);		//Keep the shape of objects.
	glutKeyboardFunc(keyboard);		//Get the keyboard input.
	glutMouseFunc(mouse);			//Get the mouse input.
	glutIdleFunc(logo_idle_display);//Logo rotating function.
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
