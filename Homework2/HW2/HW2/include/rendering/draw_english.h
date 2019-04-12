/*********************************
4104056004 李家駿 第二次作業 4/7
Functions to rendering English.
Use four ways to rendering:
	1.glDrawArrays()
	2.glDrawElements()
	3.glMultiDrawArrays()
	4.glMultiDrawElements()
*********************************/
#include "draw_includes.h"
void render_english_da(float vertices[], int number, int width, int height, float start_w)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	int j = 0, i = 0;	//The index of tmp.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height,start_w);

	/*Setting color*/
	//glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (i = 0; i < number;)
	{

		/*Initialize j*/
		j = 0;
		while (vertices[i + j] != -1)
		{
			j += 2;
		}
		glDrawArrays(GL_TRIANGLE_STRIP, i / 2, (GLsizei)(j / 2));
		i += j + 2;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height,-start_w);
}
void render_english_de(float vertices[], int number, int width, int height, float start_w)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, k;	//The index of tmp.

					/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, start_w);

	/*Setting color*/
	//glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (int i = 0; i < number;)
	{
		/*Initialize j*/
		j = 0;
		while (vertices[i + j] != -1)
		{
			j += 2;
		}
		int *indices = new int[j / 2];
		for (k = 0; k < j / 2; k++) indices[k] = i / 2 + k;
		glDrawElements(GL_TRIANGLE_STRIP, j / 2, GL_UNSIGNED_INT, indices);
		free(indices);
		i += j + 2;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, -start_w);
}
void render_english_mda(float vertices[], int number, int width, int height, float start_w)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, i = 0, k = 0;
	int *first, *count, drawcount = 0;//*first:Store the start index of polygons.
									  //*count:Store the number of vertices of polygons.
									  //drawcount:the number of polygons.

									  /*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, start_w);

	/*Setting color*/
	//glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 2;

	/*Allocate memory to *first and *count*/
	first = new int[drawcount+1];
	count = new int[drawcount+1];

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
	glMultiDrawArrays(GL_TRIANGLE_STRIP, first, count, drawcount);

	/*Free the memory*/
	free(first);
	free(count);

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, -start_w);
}
void render_english_mde(float vertices[], int number, int width, int height, float start_w)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, i = 0, k = 0;
	int  *count, drawcount = 0;	  //*count:Store the number of vertices of polygons.
								  //drawcount:the number of polygons.
	static GLvoid **indices;//**indice:Store the indices of vertices of polygons.

							/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, start_w);

	/*Setting color*/
	//glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 2;

	/*Allocate memory to *first and *count*/
	indices = new GLvoid*[drawcount+1];
	count = new int[drawcount+1];

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
	glMultiDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_BYTE, indices, drawcount);

	/*Free the memory*/
	for (i = 0; i < drawcount; i++) free(indices[i]);
	free(indices);
	free(count);

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, -start_w);
}
void render_english(int DRAW_TYPE)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	float color[3] = { 1.0,1.0,1.0 };
	glColor3fv(color);
	switch (DRAW_TYPE) {
		case MY_DRAW_ARRAYS:
			/*National*/
			render_english_da(vertices_N, sizeof(vertices_N) / sizeof(float), width, height, 25.0);
			render_english_da(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 57.0);
			render_english_da(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 86.0);
			render_english_da(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 104.0);
			render_english_da(vertices_o, sizeof(vertices_o) / sizeof(float), width, height, 115.0);
			render_english_da(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 145.0);
			render_english_da(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 174.0);
			render_english_da(vertices_l, sizeof(vertices_l) / sizeof(float), width, height, 204.0);

			/*Chung*/
			render_english_da(vertices_C, sizeof(vertices_C) / sizeof(float), width, height, 228.0);
			render_english_da(vertices_h, sizeof(vertices_h) / sizeof(float), width, height, 265.0);
			render_english_da(vertices_u, sizeof(vertices_u) / sizeof(float), width, height, 293.0);
			render_english_da(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 323.0);
			render_english_da(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 351.0);

			/*Hsing*/
			render_english_da(vertices_H, sizeof(vertices_H) / sizeof(float), width, height, 393.0);
			render_english_da(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 428.0);
			render_english_da(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 456.0);
			render_english_da(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 468.0);
			render_english_da(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 497.0);

			/*University*/
			render_english_da(vertices_U, sizeof(vertices_U) / sizeof(float), width, height, 539.0);
			render_english_da(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 574.0);
			render_english_da(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 604.0);
			render_english_da(vertices_v, sizeof(vertices_v) / sizeof(float), width, height, 616.0);
			render_english_da(vertices_e, sizeof(vertices_e) / sizeof(float), width, height, 644.0);
			render_english_da(vertices_r, sizeof(vertices_r) / sizeof(float), width, height, 673.0);
			render_english_da(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 692.0);
			render_english_da(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 718.0);
			render_english_da(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 730.0);
			render_english_da(vertices_y, sizeof(vertices_y) / sizeof(float), width, height, 747.0);
			break;
		case MY_DRAW_ELEMENTS:
			/*National*/
			render_english_de(vertices_N, sizeof(vertices_N) / sizeof(float), width, height, 25.0);
			render_english_de(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 57.0);
			render_english_de(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 86.0);
			render_english_de(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 104.0);
			render_english_de(vertices_o, sizeof(vertices_o) / sizeof(float), width, height, 115.0);
			render_english_de(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 145.0);
			render_english_de(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 174.0);
			render_english_de(vertices_l, sizeof(vertices_l) / sizeof(float), width, height, 204.0);

			/*Chung*/
			render_english_de(vertices_C, sizeof(vertices_C) / sizeof(float), width, height, 228.0);
			render_english_de(vertices_h, sizeof(vertices_h) / sizeof(float), width, height, 265.0);
			render_english_de(vertices_u, sizeof(vertices_u) / sizeof(float), width, height, 293.0);
			render_english_de(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 323.0);
			render_english_de(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 351.0);
		
			/*Hsing*/
			render_english_de(vertices_H, sizeof(vertices_H) / sizeof(float), width, height, 393.0);
			render_english_de(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 428.0);
			render_english_de(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 456.0);
			render_english_de(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 468.0);
			render_english_de(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 497.0);

			/*University*/
			render_english_de(vertices_U, sizeof(vertices_U) / sizeof(float), width, height, 539.0);
			render_english_de(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 574.0);
			render_english_de(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 604.0);
			render_english_de(vertices_v, sizeof(vertices_v) / sizeof(float), width, height, 616.0);
			render_english_de(vertices_e, sizeof(vertices_e) / sizeof(float), width, height, 644.0);
			render_english_de(vertices_r, sizeof(vertices_r) / sizeof(float), width, height, 673.0);
			render_english_de(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 692.0);
			render_english_de(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 718.0);
			render_english_de(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 730.0);
			render_english_de(vertices_y, sizeof(vertices_y) / sizeof(float), width, height, 747.0);
			break;
		case MY_MULTI_DRAW_ARRAYS:
			/*National*/
			render_english_mda(vertices_N, sizeof(vertices_N) / sizeof(float), width, height, 25.0);
			render_english_mda(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 57.0);
			render_english_mda(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 86.0);
			render_english_mda(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 104.0);
			render_english_mda(vertices_o, sizeof(vertices_o) / sizeof(float), width, height, 115.0);
			render_english_mda(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 145.0);
			render_english_mda(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 174.0);
			render_english_mda(vertices_l, sizeof(vertices_l) / sizeof(float), width, height, 204.0);

			/*Chung*/
			render_english_mda(vertices_C, sizeof(vertices_C) / sizeof(float), width, height, 228.0);
			render_english_mda(vertices_h, sizeof(vertices_h) / sizeof(float), width, height, 265.0);
			render_english_mda(vertices_u, sizeof(vertices_u) / sizeof(float), width, height, 293.0);
			render_english_mda(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 323.0);
			render_english_mda(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 351.0);

			/*Hsing*/
			render_english_mda(vertices_H, sizeof(vertices_H) / sizeof(float), width, height, 393.0);
			render_english_mda(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 428.0);
			render_english_mda(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 456.0);
			render_english_mda(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 468.0);
			render_english_mda(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 497.0);

			/*University*/
			render_english_mda(vertices_U, sizeof(vertices_U) / sizeof(float), width, height, 539.0);
			render_english_mda(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 574.0);
			render_english_mda(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 604.0);
			render_english_mda(vertices_v, sizeof(vertices_v) / sizeof(float), width, height, 616.0);
			render_english_mda(vertices_e, sizeof(vertices_e) / sizeof(float), width, height, 644.0);
			render_english_mda(vertices_r, sizeof(vertices_r) / sizeof(float), width, height, 673.0);
			render_english_mda(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 692.0);
			render_english_mda(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 718.0);
			render_english_mda(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 730.0);
			render_english_mda(vertices_y, sizeof(vertices_y) / sizeof(float), width, height, 747.0);
			break;
		case MY_MULTI_DRAW_ELEMENTS:
			/*National*/
			render_english_mde(vertices_N, sizeof(vertices_N) / sizeof(float), width, height, 25.0);
			render_english_mde(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 57.0);
			render_english_mde(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 86.0);
			render_english_mde(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 104.0);
			render_english_mde(vertices_o, sizeof(vertices_o) / sizeof(float), width, height, 115.0);
			render_english_mde(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 145.0);
			render_english_mde(vertices_a, sizeof(vertices_a) / sizeof(float), width, height, 174.0);
			render_english_mde(vertices_l, sizeof(vertices_l) / sizeof(float), width, height, 204.0);
			
			/*Chung*/
			render_english_mde(vertices_C, sizeof(vertices_C) / sizeof(float), width, height, 228.0);
			render_english_mde(vertices_h, sizeof(vertices_h) / sizeof(float), width, height, 265.0);
			render_english_mde(vertices_u, sizeof(vertices_u) / sizeof(float), width, height, 293.0);
			render_english_mde(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 323.0);
			render_english_mde(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 351.0);
			
			/*Hsing*/
			render_english_mde(vertices_H, sizeof(vertices_H) / sizeof(float), width, height, 393.0);
			render_english_mde(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 428.0);
			render_english_mde(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 456.0);
			render_english_mde(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 468.0);
			render_english_mde(vertices_g, sizeof(vertices_g) / sizeof(float), width, height, 497.0);
			
			/*University*/
			render_english_mde(vertices_U, sizeof(vertices_U) / sizeof(float), width, height, 539.0);
			render_english_mde(vertices_n, sizeof(vertices_n) / sizeof(float), width, height, 574.0);
			render_english_mde(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 604.0);
			render_english_mde(vertices_v, sizeof(vertices_v) / sizeof(float), width, height, 616.0);
			render_english_mde(vertices_e, sizeof(vertices_e) / sizeof(float), width, height, 644.0);
			render_english_mde(vertices_r, sizeof(vertices_r) / sizeof(float), width, height, 673.0);
			render_english_mde(vertices_s, sizeof(vertices_s) / sizeof(float), width, height, 692.0);
			render_english_mde(vertices_i, sizeof(vertices_i) / sizeof(float), width, height, 718.0);
			render_english_mde(vertices_t, sizeof(vertices_t) / sizeof(float), width, height, 730.0);
			render_english_mde(vertices_y, sizeof(vertices_y) / sizeof(float), width, height, 747.0);
			break;
		default:
			break;
	}
	
}