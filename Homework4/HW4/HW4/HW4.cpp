// HW4.cpp : 定義主控台應用程式的進入點。
//
/*********************************
4104056004 李家駿 第四次作業 5/1
**********************************
The Main function
Functions:
	Keyboard 1:Rotate the upper arm					
	Keyboard 2:Rotate the lower arm					
	Keyboard 3:Rotate the fist sections of fingers	
	Keyboard 4:Rotate the thumb						
	Keyboard W:	Move forward						
	Keyboard S:	Move backward						
	Keyboard A:	Move left							
	Keyboard D:	Move right							
	Mouse Right click: Rotate the scene by x-axis	
	Mouse Left  click: Rotate the scene by z-axis	
	Mouse Middle click: Rotate the scene by y-axis	
	idleFunc:Planet rotate							
*********************************/
#include "stdafx.h"
#include "rendering_robot_and_planet\draw_all.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
static float camera_x = 0, camera_y = 0, camera_z = 3;
static float angle_x = 0, angle_y = 0, angle_z = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)500 / (GLfloat)500, 1.0, 20.0);
	glShadeModel(GL_FLAT);
	srand(time(NULL));
	camera_x = 4;
	camera_y = 0;
	camera_z = 7;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
}
void planet_idle_display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glPushMatrix();
		/*Rotate camera*/
		glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
		glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
		glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

		/*Set the speed of evolution and rotation*/
		earth_day = (earth_day + 50) % 360;
		earth_year = (earth_year + 1) % 360;

		/*Draw earth*/
		glPushMatrix();
			//glRotatef(shoulder_angle, 0, 0, 1);				//Rotate with arm
			glTranslatef((arm_length * 2 + 2), 0, 0);
			rendering_earth();
		glPopMatrix();
	glPopMatrix();
	glutPostRedisplay();
	glutSwapBuffers();
}
void display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glPushMatrix();
		/*Rotate camera*/
		glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
		glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
		glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

		/* clear all pixels  */
		glClear(GL_COLOR_BUFFER_BIT);

		/*Draw the arm and elbow.*/
		glTranslatef(arm_length / 2, 0, 0);
		rendering_arm_and_elbow();
		glTranslatef(-arm_length / 2, 0, 0);

		/*Draw the fingers*/
		glPushMatrix();
			glRotatef(shoulder_angle, 0, 0, 1);					//Rotate with arm.

			glTranslatef(arm_length, (float)arm_height/2, 0);
			glRotatef(elbow_angle, 0, 0, 1);					//Rotate with elbow
			glTranslatef(-arm_length, -(float)arm_height / 2, 0);

			glTranslatef(arm_length * 2, 0, 0);					//Move to hand's position
			
			/*Rendering*/
			rendering_finger();
			rendering_thumb();
		glPopMatrix();

		/*Draw sun*/
		glPushMatrix();
			//glRotatef(shoulder_angle, 0, 0, 1);				//Rotate with arm
			glTranslatef((arm_length * 2 + 2), 0, 0);
			rendering_orbit();
			rendering_sun();
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w>h)
		gluPerspective(65.0, 1 * (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	else
		gluPerspective(65.0*(GLfloat)h / (GLfloat)w, 1, 1.0, 20.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		/*Robot move*/
		case '1':
			/*Rotate shoulder*/
			shoulder_angle = (shoulder_angle + 5) % 360;
			glutPostRedisplay();
			break;
		case '2':
			/*Rotate elbow*/
			elbow_angle = (elbow_angle + elbow_shift) % 360;
			if (elbow_angle >= 180)		//Touch the arm.Turn back.
				elbow_shift = -5;
			else if (elbow_angle <= 0)	//Totally extended.Turn back.
				elbow_shift = 5;
			glutPostRedisplay();
			break;
		case '3':
			/*Rotate finger*/
			finger_and_thumb_move = 1;	//Rotate thumb and finger at the same time.
			finger_angle = (finger_angle - finger_shift) % 360;

			/*Avoid fingers touch each other.*/
			if (finger_angle <= -60 || (finger_angle < 0 && thumb_angle <= -6))		//Totally extended.Turn back.
				finger_shift = -3;
			else if (finger_angle >= 60)	//Touch the second setion.Turn back.
				finger_shift = 3;

			/*Redraw*/
			glutPostRedisplay();
			break;
		case '4':
			/*Rotate thumb*/
			finger_and_thumb_move = 0;		//Only move thumb.
			thumb_angle = (thumb_angle + thumb_shift) % 360;

			/*Avoid fingers touch each other.*/
			if (thumb_angle >= 60)		//Touch the second setion.Turn back.
				thumb_shift = -3;
			else if (thumb_angle <= -60 || (thumb_angle<0 && finger_angle <= -6))	//Totally extended.Turn back.
				thumb_shift = 3;
			
			/*Redraw*/
			glutPostRedisplay();
			break;

		/*Move camera*/
		case 'W':
			/*Move forward.*/
			camera_z -= 0.1;
			glutPostRedisplay();
			break;
		case 'w':
			camera_z -= 0.1;
			glutPostRedisplay();
			break;
		case 'S':
			/*Move backward.*/
			camera_z += 0.1;
			glutPostRedisplay();
			break;
		case 's':
			camera_z += 0.1;
			glutPostRedisplay();
			break;
		case 'A':
			/*Move left.*/
			camera_x -= 0.2;
			glutPostRedisplay();
			break;
		case 'a':
			camera_x -= 0.2;
			glutPostRedisplay();
			break;
		case 'D':
			/*Move forward.*/
			camera_x += 0.2;
			glutPostRedisplay();
			break;
		case 'd':
			camera_x += 0.2;
			glutPostRedisplay();
			break;
			/*Other*/
		case '0':
			init();
			init_robot_and_planet();
			glutPostRedisplay();
			break;
		default:
			break;
	}
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)	//Rotate by z-axis while press left button of mouse.
		{
			angle_z = ((int)angle_z + 30) % 360;
			glutPostRedisplay();
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)	//Rotate by y-axis while press left button of mouse.
		{
			angle_y = ((int)angle_y + 10) % 360;
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)	//Rotate by x-axis while press left button of mouse.
		{
			angle_x = ((int)angle_x + 30) % 360;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
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
	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework4");
	init();
	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);		//Keep the shape of objects.
	glutKeyboardFunc(keyboard);		//Get the keyboard input.
	glutMouseFunc(mouse);			//Get the mouse input.
	glutIdleFunc(planet_idle_display);//Planet rotating function.
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
