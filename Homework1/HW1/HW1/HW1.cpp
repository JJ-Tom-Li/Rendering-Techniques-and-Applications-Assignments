// HW1.cpp : 定義主控台應用程式的進入點。
//
/*********************************
4104056004 李家駿 第一次作業 3/27
*********************************/
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\glut.h"
#include "nchu\coordinates.h" 
#include <stdlib.h>
#include <iostream>
using namespace std;
void pixel_reverse(float vertices[],int number,int width,int height)
{
	for (int i = 0; i<number; i += 2)
	{
		if (vertices[i] == -1) continue;
		//vertices[i] = (vertices[i]) / width;
		vertices[i+1] = ((float)height - vertices[i+1]);
	}
}
void render_chinese(float vertices[], int number, int width, int height, float color[3])
{
	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height);
	
	/*Setting color*/
	glColor3fv(color);

	/*Draw the word*/
	for (int i = 0; i < number;)
	{
		glBegin(GL_POLYGON);
			while (vertices[i] != -1)
			{
				//cout << i << ":" << vertices[i] << " " << vertices[i + 1] << endl;
				glVertex2f(vertices[i], vertices[i + 1]);
				i += 2;
			}
			i += 2;
		glEnd();
	}

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height);
}
void render_chinese(void)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	float color[3] = { 1.0,1.0,1.0 };
	render_chinese(vertices_ch1,sizeof(vertices_ch1)/sizeof(float),width,height, color);
	render_chinese(vertices_ch2, sizeof(vertices_ch2) / sizeof(float), width, height, color);
	render_chinese(vertices_ch3, sizeof(vertices_ch3) / sizeof(float), width, height, color);
	render_chinese(vertices_ch4, sizeof(vertices_ch4) / sizeof(float), width, height, color);
	render_chinese(vertices_ch5, sizeof(vertices_ch5) / sizeof(float), width, height, color);
	render_chinese(vertices_ch6, sizeof(vertices_ch6) / sizeof(float), width, height, color);

}
void render_logo(void)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	float color1[3] = { .0,0.3,1.0 };
	render_chinese(vertices_logo_square, sizeof(vertices_logo_square) / sizeof(float), width, height,color1);
	float color2[3] = { 1.0,0,0 };
	render_chinese(vertices_logo_circle, sizeof(vertices_logo_circle) / sizeof(float), width, height,color2);
}
void render_english(float vertices[], int number, int width, int height,float start_w)
{
	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height);

	/*Setting color*/
	glColor3f(1.0, 1.0, 1.0);

	/*Draw the word*/
	for (int i = 0; i < number;)
	{
		glBegin(GL_TRIANGLE_STRIP);
		while (vertices[i] != -1)
		{
			//cout << i << ":" << start_w+vertices[i] << " " <<+ vertices[i + 1] << endl;
			glVertex2f(start_w+vertices[i], vertices[i + 1]);
			i += 2;
		}
		i += 2;
		glEnd();
	}

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height);
}
void render_english(void)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	//float start_w = 25.0;//,start_h = height-217.0; //Store the start position of words.
	/*National*/
	render_english(vertices_N, sizeof(vertices_N) / sizeof(float), width, height,25.0);
	render_english(vertices_a, sizeof(vertices_a) / sizeof(float), width, height,57.0);
	render_english(vertices_t, sizeof(vertices_t) / sizeof(float), width, height,86.0);
	render_english(vertices_i, sizeof(vertices_i) / sizeof(float), width, height,104.0);
	render_english(vertices_o, sizeof(vertices_o) / sizeof(float), width, height,115.0);
	render_english(vertices_n, sizeof(vertices_n) / sizeof(float), width, height,145.0);
	render_english(vertices_a, sizeof(vertices_a) / sizeof(float), width, height,174.0);
	render_english(vertices_l, sizeof(vertices_l) / sizeof(float), width, height,204.0);

	/*Chung*/
	render_english(vertices_C, sizeof(vertices_C) / sizeof(float), width, height,228.0);
	render_english(vertices_h, sizeof(vertices_h) / sizeof(float), width, height,265.0);
	render_english(vertices_u, sizeof(vertices_u) / sizeof(float), width, height,293.0);
	render_english(vertices_n, sizeof(vertices_n) / sizeof(float), width, height,323.0);
	render_english(vertices_g, sizeof(vertices_g) / sizeof(float), width, height,351.0);

	/*Hsing*/
	render_english(vertices_H, sizeof(vertices_H) / sizeof(float), width, height,393.0);
	render_english(vertices_s, sizeof(vertices_s) / sizeof(float), width, height,428.0);
	render_english(vertices_i, sizeof(vertices_i) / sizeof(float), width, height,456.0);
	render_english(vertices_n, sizeof(vertices_n) / sizeof(float), width, height,468.0);
	render_english(vertices_g, sizeof(vertices_g) / sizeof(float), width, height,497.0);

	/*University*/
	render_english(vertices_U, sizeof(vertices_U) / sizeof(float), width, height,539.0);
	render_english(vertices_n, sizeof(vertices_n) / sizeof(float), width, height,574.0);
	render_english(vertices_i, sizeof(vertices_i) / sizeof(float), width, height,604.0);
	render_english(vertices_v, sizeof(vertices_v) / sizeof(float), width, height,616.0);
	render_english(vertices_e, sizeof(vertices_e) / sizeof(float), width, height,644.0);
	render_english(vertices_r, sizeof(vertices_r) / sizeof(float), width, height,673.0);
	render_english(vertices_s, sizeof(vertices_s) / sizeof(float), width, height,692.0);
	render_english(vertices_i, sizeof(vertices_i) / sizeof(float), width, height,718.0);
	render_english(vertices_t, sizeof(vertices_t) / sizeof(float), width, height,730.0);
	render_english(vertices_y, sizeof(vertices_y) / sizeof(float), width, height,747.0);

}
void display(void)
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
	render_chinese();

	/*Draw the mark part*/
	render_logo ();

	/*Draw the english part*/
	render_english();

	glutSwapBuffers();
	/* don't wait!
	* start processing buffered OpenGL routines
	*/
	// glFlush ();
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
	glutCreateWindow("Homework1");
	init();
	glewInit();
	
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
