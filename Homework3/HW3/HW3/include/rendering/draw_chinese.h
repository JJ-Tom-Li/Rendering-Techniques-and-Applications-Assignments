/*********************************
4104056004 李家駿 第二次作業 4/7
Functions to rendering chinese and logo.
Use four ways to rendering:
	1.glDrawArrays()
	2.glDrawElements()
	3.glMultiDrawArrays()
	4.glMultiDrawElements()
*********************************/
#include "rendering\draw_english.h"
void render_chinese_da(float vertices[], int number, int width, int height, float color[3])
{
	//cout << "DA START\n";
	glEnableClientState(GL_VERTEX_ARRAY);

	int j = 0,i=0;	//The index of tmp.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height,0);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (i = 0; i < number;)
	{

		/*Initialize j*/
		j = 0;
		while (vertices[i+j] != -1)
		{
			j += 3;
			//if (i + j > number) break;
		}
		glDrawArrays(GL_POLYGON, i/3,(GLsizei)(j/3));
		i+=j+3;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, 0);
}
void render_chinese_de(float vertices[], int number, int width, int height, float color[3])
{
	//cout << "DE START\n";
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0,k;	//The index of tmp.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, 0);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (int i = 0; i < number;)
	{
		/*Initialize j*/
		j = 0;
		while (vertices[i+j] != -1)
		{
			j += 3;
		}
		int *indices = new int[j/2];
		for (k = 0; k < j / 3; k++) indices[k] = i/3+k;
		glDrawElements(GL_POLYGON, j/3, GL_UNSIGNED_INT,indices);
		free(indices);
		i += j+3;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, 0);
}
void render_chinese_mda(float vertices[], int number, int width, int height, float color[3])
{
	//cout << "MDA START\n";
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, i = 0,k=0;
	int *first, *count, drawcount=0;//*first:Store the start index of polygons.
									//*count:Store the number of vertices of polygons.
									//drawcount:the number of polygons.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, 0);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 3;

	/*Allocate memory to *first and *count*/
	first = new int[drawcount];
	count = new int[drawcount];

	/*Draw the word*/
	for (i = 0; i < number;)
	{
		j = 0;		//Initialize j
		while (vertices[i + j] != -1)	//Count the number of vertices.
		{
			j += 3;
		}
		first[k] = i / 3;		//Get first and count.
		count[k++] = j / 3;
		i += j + 3;
	}
	glMultiDrawArrays(GL_POLYGON, first, count, drawcount);

	
	/*Free the memory*/
	free(first);
	free(count);

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, 0);
}
void render_chinese_mde(float vertices[], int number, int width, int height, float color[3])
{
	//cout << "MDE START\n";
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, i = 0, k = 0;
	int  *count, drawcount = 0;	  //*count:Store the number of vertices of polygons.
								  //drawcount:the number of polygons.
	static GLvoid **indices;//**indice:Store the indices of vertices of polygons.
								
	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, 0);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 3;

	/*Allocate memory to *first and *count*/
	indices = new GLvoid*[drawcount];
	count = new int[drawcount];

	/*Draw the word*/
	for (i = 0; i < number;)
	{
		j = 0;		//Initialize j
		while (vertices[i + j] != -1)	//Count the number of vertices.
		{
			j += 3;
		}
		GLubyte *indices_element = new GLubyte[j / 3];
		for (int k = 0; k < j / 3; k++) indices_element[k] = i / 3 + k;
		indices[k] = indices_element;
		count[k++] = j / 3;
		i += j + 3;
		
	}
	glMultiDrawElements(GL_POLYGON, count, GL_UNSIGNED_BYTE, indices, drawcount);

	/*Free the memory*/
	for (i = 0; i < drawcount; i++) free(indices[i]);
	free(indices);
	free(count);

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, 0);
}
void render_chinese(int DRAW_TYPE)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	//float color[3] = { 1.0,1.0,1.0 };
	/*According to the argument DRAW_TPYE.The function will use different ways to draw polygons.*/
	switch (DRAW_TYPE) {
		case MY_DRAW_ARRAYS:
			render_chinese_da(ch1.vertices, ch1.vnumber, width, height, ch1.color);
			render_chinese_da(ch2.vertices, ch2.vnumber, width, height, ch2.color);
			render_chinese_da(ch3.vertices, ch3.vnumber, width, height, ch3.color);
			render_chinese_da(ch4.vertices, ch4.vnumber, width, height, ch4.color);
			render_chinese_da(ch5.vertices, ch5.vnumber, width, height, ch5.color);
			render_chinese_da(ch6.vertices, ch6.vnumber, width, height, ch6.color);
			break;
		case MY_DRAW_ELEMENTS:
			render_chinese_de(ch1.vertices, ch1.vnumber, width, height, ch1.color);
			render_chinese_de(ch2.vertices, ch2.vnumber, width, height, ch2.color);
			render_chinese_de(ch3.vertices, ch3.vnumber, width, height, ch3.color);
			render_chinese_de(ch4.vertices, ch4.vnumber, width, height, ch4.color);
			render_chinese_de(ch5.vertices, ch5.vnumber, width, height, ch5.color);
			render_chinese_de(ch6.vertices, ch6.vnumber, width, height, ch6.color); 
			break;
		case MY_MULTI_DRAW_ARRAYS:
			render_chinese_mda(ch1.vertices, ch1.vnumber, width, height, ch1.color);
			render_chinese_mda(ch2.vertices, ch2.vnumber, width, height, ch2.color);
			render_chinese_mda(ch3.vertices, ch3.vnumber, width, height, ch3.color);
			render_chinese_mda(ch4.vertices, ch4.vnumber, width, height, ch4.color);
			render_chinese_mda(ch5.vertices, ch5.vnumber, width, height, ch5.color);
			render_chinese_mda(ch6.vertices, ch6.vnumber, width, height, ch6.color); 
			break;
		case MY_MULTI_DRAW_ELEMENTS:
			render_chinese_mde(ch1.vertices, ch1.vnumber, width, height, ch1.color);
			render_chinese_mde(ch2.vertices, ch2.vnumber, width, height, ch2.color);
			render_chinese_mde(ch3.vertices, ch3.vnumber, width, height, ch3.color);
			render_chinese_mde(ch4.vertices, ch4.vnumber, width, height, ch4.color);
			render_chinese_mde(ch5.vertices, ch5.vnumber, width, height, ch5.color);
			render_chinese_mde(ch6.vertices, ch6.vnumber, width, height, ch6.color); 
			break;
		default:
			break;
	}
	
}
void render_logo(int DRAW_TYPE)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	switch (DRAW_TYPE) {
	case MY_DRAW_ARRAYS:
		render_chinese_da(logo_square.vertices, logo_square.vnumber, width, height, logo_square.color);
		render_chinese_da(logo_circle.vertices, logo_circle.vnumber, width, height, logo_circle.color);
		break;
	case MY_DRAW_ELEMENTS:
		render_chinese_de(logo_square.vertices, logo_square.vnumber, width, height, logo_square.color);
		render_chinese_de(logo_circle.vertices, logo_circle.vnumber, width, height, logo_circle.color); 
		break;
	case MY_MULTI_DRAW_ARRAYS:
		render_chinese_mda(logo_square.vertices, logo_square.vnumber, width, height, logo_square.color);
		render_chinese_mda(logo_circle.vertices, logo_circle.vnumber, width, height, logo_circle.color); 
		break;
	case MY_MULTI_DRAW_ELEMENTS:
		render_chinese_mde(logo_square.vertices, logo_square.vnumber, width, height, logo_square.color);
		render_chinese_mde(logo_circle.vertices, logo_circle.vnumber, width, height, logo_circle.color); 
		break;
	default:
		break;
	}
}