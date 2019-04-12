// HW1.cpp : 定義主控台應用程式的進入點。
//
/*********************************
4104056004 李家駿 第二次作業 4/7
The Main function
*********************************/
#include "stdafx.h"
#include "rendering/draw_all.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

void display_clear()
{
	/* clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}
void display(int DRAW_TYPE)
{
	/* clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	/* draw white polygon (rectangle) with corners at
	* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
	*/

	/*Draw the chinese part*/
	render_chinese(DRAW_TYPE);

	/*Draw the mark part*/
	render_logo(DRAW_TYPE);

	/*Draw the english part*/
	render_english(DRAW_TYPE);

	glutSwapBuffers();
	/* don't wait!
	* start processing buffered OpenGL routines
	*/
	// glFlush ();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1':
			display(MY_DRAW_ARRAYS);	
			break;
		case '2':
			display(MY_DRAW_ELEMENTS);
			break;
		case '3':
			display(MY_MULTI_DRAW_ARRAYS);
			break;
		case '4':
			display(MY_MULTI_DRAW_ELEMENTS);
			break;
		case '0':
			display_clear();
			break;
		default:
			break;
	}
}

void init(void)
{
	/* select clearing color 	*/
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 790, 0, 274);
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
	glutInitWindowSize(790, 274);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework2");
	init();
	glewInit();

	glutDisplayFunc(display_clear);
	glutKeyboardFunc(keyboard);		//Get the keyboard input.
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
