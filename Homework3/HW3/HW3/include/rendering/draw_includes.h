/*********************************
4104056004 李家駿 第二次作業 4/7
Include all files and funcitons needed.
*********************************/
#include "GL\glew.h"
#include "GL\glut.h"
//#include "nchu\coordinates.h"
#include "nchu\rendering_objects.h"
#include <iostream>
#define MY_DRAW_ARRAYS 0
#define MY_DRAW_ELEMENTS 1
#define MY_MULTI_DRAW_ARRAYS 2
#define MY_MULTI_DRAW_ELEMENTS 3
#define NCHU_WIDTH 790
#define NCHU_HEIGHT 274
using namespace std;
void pixel_reverse(float vertices[], int number, int width, int height,float start_w)
{
	for (int i = 0; i<number; i += 3)
	{
		if (vertices[i] == -1) continue;
		vertices[i] = (vertices[i]) + start_w;
		vertices[i + 1] = ((float)height - vertices[i + 1]);
	}
}