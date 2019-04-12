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
	cout << "DA START\n";
	glEnableClientState(GL_VERTEX_ARRAY);

	int j = 0,i=0;	//The index of tmp.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height,0);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (i = 0; i < number;)
	{

		/*Initialize j*/
		j = 0;
		while (vertices[i+j] != -1)
		{
			j += 2;
		}
		glDrawArrays(GL_POLYGON, i/2,(GLsizei)(j/2));
		i+=j+2;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, 0);
}
void render_chinese_de(float vertices[], int number, int width, int height, float color[3])
{
	cout << "DE START\n";
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0,k;	//The index of tmp.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, 0);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (int i = 0; i < number;)
	{
		/*Initialize j*/
		j = 0;
		while (vertices[i+j] != -1)
		{
			j += 2;
		}
		int *indices = new int[j/2];
		for (k = 0; k < j / 2; k++) indices[k] = i/2+k;
		glDrawElements(GL_POLYGON, j/2, GL_UNSIGNED_INT,indices);
		free(indices);
		i += j+2;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, 0);
}
void render_chinese_mda(float vertices[], int number, int width, int height, float color[3])
{
	cout << "MDA START\n";
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
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 2;

	/*Allocate memory to *first and *count*/
	first = new int[drawcount];
	count = new int[drawcount];

	/*Draw the word*/
	for (i = 0; i < number;)
	{
		j = 0;		//Initialize j
		while (vertices[i + j] != -1)	//Count the number of vertices.
		{
			j += 2;
		}
		first[k] = i / 2;		//Get first and count.
		count[k++] = j / 2;
		i += j + 2;
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
	cout << "MDE START\n";
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
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 2;

	/*Allocate memory to *first and *count*/
	indices = new GLvoid*[drawcount];
	count = new int[drawcount];

	/*Draw the word*/
	for (i = 0; i < number;)
	{
		j = 0;		//Initialize j
		while (vertices[i + j] != -1)	//Count the number of vertices.
		{
			j += 2;
		}
		GLubyte *indices_element = new GLubyte[j / 2];
		for (int k = 0; k < j / 2; k++) indices_element[k] = i / 2 + k;
		indices[k] = indices_element;
		count[k++] = j / 2;
		i += j + 2;
		
	}
	glMultiDrawElements(GL_POLYGON, count, GL_UNSIGNED_BYTE, indices, drawcount);

	for (i = 0; i < drawcount ;i++)
	{
		for (j = 0; j < count[i]; j++)
		{
			GLubyte *indices_element = (GLubyte*)indices[i];
			cout << (int)indices_element[j] << " ";
		}
		cout << endl;
	}
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
	float color[3] = { 1.0,1.0,1.0 };
	/*According to the argument DRAW_TPYE.The function will use different ways to draw polygons.*/
	switch (DRAW_TYPE) {
		case MY_DRAW_ARRAYS:
			render_chinese_da(vertices_ch1, sizeof(vertices_ch1) / sizeof(float), width, height, color);
			render_chinese_da(vertices_ch2, sizeof(vertices_ch2) / sizeof(float), width, height, color);
			render_chinese_da(vertices_ch3, sizeof(vertices_ch3) / sizeof(float), width, height, color);
			render_chinese_da(vertices_ch4, sizeof(vertices_ch4) / sizeof(float), width, height, color);
			render_chinese_da(vertices_ch5, sizeof(vertices_ch5) / sizeof(float), width, height, color);
			render_chinese_da(vertices_ch6, sizeof(vertices_ch6) / sizeof(float), width, height, color);
			break;
		case MY_DRAW_ELEMENTS:
			render_chinese_de(vertices_ch1, sizeof(vertices_ch1) / sizeof(float), width, height, color);
			render_chinese_de(vertices_ch2, sizeof(vertices_ch2) / sizeof(float), width, height, color);
			render_chinese_de(vertices_ch3, sizeof(vertices_ch3) / sizeof(float), width, height, color);
			render_chinese_de(vertices_ch4, sizeof(vertices_ch4) / sizeof(float), width, height, color);
			render_chinese_de(vertices_ch5, sizeof(vertices_ch5) / sizeof(float), width, height, color);
			render_chinese_de(vertices_ch6, sizeof(vertices_ch6) / sizeof(float), width, height, color);
			break;
		case MY_MULTI_DRAW_ARRAYS:
			render_chinese_mda(vertices_ch1, sizeof(vertices_ch1) / sizeof(float), width, height, color);
			render_chinese_mda(vertices_ch2, sizeof(vertices_ch2) / sizeof(float), width, height, color);
			render_chinese_mda(vertices_ch3, sizeof(vertices_ch3) / sizeof(float), width, height, color);
			render_chinese_mda(vertices_ch4, sizeof(vertices_ch4) / sizeof(float), width, height, color);
			render_chinese_mda(vertices_ch5, sizeof(vertices_ch5) / sizeof(float), width, height, color);
			render_chinese_mda(vertices_ch6, sizeof(vertices_ch6) / sizeof(float), width, height, color);
			break;
		case MY_MULTI_DRAW_ELEMENTS:
			render_chinese_mde(vertices_ch1, sizeof(vertices_ch1) / sizeof(float), width, height, color);
			render_chinese_mde(vertices_ch2, sizeof(vertices_ch2) / sizeof(float), width, height, color);
			render_chinese_mde(vertices_ch3, sizeof(vertices_ch3) / sizeof(float), width, height, color);
			render_chinese_mde(vertices_ch4, sizeof(vertices_ch4) / sizeof(float), width, height, color);
			render_chinese_mde(vertices_ch5, sizeof(vertices_ch5) / sizeof(float), width, height, color);
			render_chinese_mde(vertices_ch6, sizeof(vertices_ch6) / sizeof(float), width, height, color);
			break;
		default:
			break;
	}
	
}
void render_logo(int DRAW_TYPE)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	float color1[3] = { .0f,0.3f,1.0f }; 
	float color2[3] = { 1.0f,.0f,.0f };
	switch (DRAW_TYPE) {
	case MY_DRAW_ARRAYS:
		render_chinese_da(vertices_logo_square, sizeof(vertices_logo_square) / sizeof(float), width, height, color1);
		render_chinese_da(vertices_logo_circle, sizeof(vertices_logo_circle) / sizeof(float), width, height, color2);
		break;
	case MY_DRAW_ELEMENTS:
		render_chinese_de(vertices_logo_square, sizeof(vertices_logo_square) / sizeof(float), width, height, color1);
		render_chinese_de(vertices_logo_circle, sizeof(vertices_logo_circle) / sizeof(float), width, height, color2);
		break;
	case MY_MULTI_DRAW_ARRAYS:
		render_chinese_mda(vertices_logo_square, sizeof(vertices_logo_square) / sizeof(float), width, height, color1);
		render_chinese_mda(vertices_logo_circle, sizeof(vertices_logo_circle) / sizeof(float), width, height, color2);
		break;
	case MY_MULTI_DRAW_ELEMENTS:
		render_chinese_mde(vertices_logo_square, sizeof(vertices_logo_square) / sizeof(float), width, height, color1);
		render_chinese_mde(vertices_logo_circle, sizeof(vertices_logo_circle) / sizeof(float), width, height, color2);
		break;
	default:
		break;
	}
}