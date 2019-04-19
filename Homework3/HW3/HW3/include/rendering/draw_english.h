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
void render_english_da(float vertices[], int number, int width, int height, float start_w, float color[])
{
	glEnableClientState(GL_VERTEX_ARRAY);

	int j = 0, i = 0;	//The index of tmp.

	/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height,start_w);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (i = 0; i < number;)
	{

		/*Initialize j*/
		j = 0;
		while (vertices[i + j] != -1)
		{
			j += 3;
		}
		glDrawArrays(GL_TRIANGLE_STRIP, i / 3, (GLsizei)(j / 3));
		i += j + 3;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height,-start_w);
}
void render_english_de(float vertices[], int number, int width, int height, float start_w, float color[])
{
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, k;	//The index of tmp.

					/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, start_w);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Draw the word*/
	for (int i = 0; i < number;)
	{
		/*Initialize j*/
		j = 0;
		while (vertices[i + j] != -1)
		{
			j += 3;
		}
		int *indices = new int[j / 2];
		for (k = 0; k < j / 3; k++) indices[k] = i / 3 + k;
		glDrawElements(GL_TRIANGLE_STRIP, j / 3, GL_UNSIGNED_INT, indices);
		free(indices);
		i += j + 3;
	}
	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, -start_w);
}
void render_english_mda(float vertices[], int number, int width, int height, float start_w, float color[])
{
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, i = 0, k = 0;
	int *first, *count, drawcount = 0;//*first:Store the start index of polygons.
									  //*count:Store the number of vertices of polygons.
									  //drawcount:the number of polygons.

									  /*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, start_w);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 3;

	/*Allocate memory to *first and *count*/
	first = new int[drawcount+1];
	count = new int[drawcount+1];

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
	glMultiDrawArrays(GL_TRIANGLE_STRIP, first, count, drawcount);

	/*Free the memory*/
	free(first);
	free(count);

	/*Reverse again.*/
	pixel_reverse(vertices, number, width, height, -start_w);
}
void render_english_mde(float vertices[], int number, int width, int height, float start_w,float color[])
{
	glEnableClientState(GL_VERTEX_ARRAY);
	int j = 0, i = 0, k = 0;
	int  *count, drawcount = 0;	  //*count:Store the number of vertices of polygons.
								  //drawcount:the number of polygons.
	static GLvoid **indices;//**indice:Store the indices of vertices of polygons.

							/*Due to the coordinates of Painter is reverse.We need to reverse the coordinates first.*/
	pixel_reverse(vertices, number, width, height, start_w);

	/*Setting color*/
	glColor3fv(color);

	/*Declare the vertex pointer*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	/*Get the number of polygons.*/
	for (int i = 0; i < number; i++)
		if (vertices[i] == -1) drawcount++;
	drawcount /= 3;

	/*Allocate memory to *first and *count*/
	indices = new GLvoid*[drawcount+1];
	count = new int[drawcount+1];

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
	//float color[3] = { 1.0,1.0,1.0 };
	//glColor3fv(color);
	switch (DRAW_TYPE) {
		case MY_DRAW_ARRAYS:
			/*National*/
			render_english_da(letter_N.vertices,letter_N.vnumber, width, height, 25.0,letter_N.color);
			render_english_da(letter_a.vertices, letter_a.vnumber, width, height, 57.0, letter_a.color);
			render_english_da(letter_t.vertices, letter_t.vnumber, width, height, 86.0, letter_t.color);
			render_english_da(letter_i.vertices, letter_i.vnumber, width, height, 104.0, letter_i.color);
			render_english_da(letter_o.vertices, letter_o.vnumber, width, height, 115.0, letter_o.color);
			render_english_da(letter_n.vertices, letter_n.vnumber, width, height, 145.0, letter_n.color);
			render_english_da(letter_a.vertices, letter_a.vnumber, width, height, 174.0, letter_a.color);
			render_english_da(letter_l.vertices, letter_l.vnumber, width, height, 204.0, letter_l.color);

			/*Chung*/
			render_english_da(letter_C.vertices, letter_C.vnumber, width, height, 228.0, letter_C.color);
			render_english_da(letter_h.vertices, letter_h.vnumber, width, height, 265.0, letter_h.color);
			render_english_da(letter_u.vertices, letter_u.vnumber, width, height, 293.0, letter_u.color);
			render_english_da(letter_n.vertices, letter_n.vnumber, width, height, 323.0, letter_n.color);
			render_english_da(letter_g.vertices, letter_g.vnumber, width, height, 351.0, letter_g.color);

			/*Hsing*/
			render_english_da(letter_H.vertices, letter_H.vnumber, width, height, 393.0, letter_H.color);
			render_english_da(letter_s.vertices, letter_s.vnumber, width, height, 428.0, letter_s.color);
			render_english_da(letter_i.vertices, letter_i.vnumber, width, height, 456.0, letter_i.color);
			render_english_da(letter_n.vertices, letter_n.vnumber, width, height, 468.0, letter_n.color);
			render_english_da(letter_g.vertices, letter_g.vnumber, width, height, 497.0, letter_g.color);

			/*University*/
			render_english_da(letter_U.vertices, letter_U.vnumber, width, height, 539.0,letter_U.color);
			render_english_da(letter_n.vertices, letter_n.vnumber, width, height, 574.0, letter_n.color);
			render_english_da(letter_i.vertices, letter_i.vnumber, width, height, 604.0, letter_i.color);
			render_english_da(letter_v.vertices, letter_v.vnumber, width, height, 616.0, letter_v.color);
			render_english_da(letter_e.vertices, letter_e.vnumber, width, height, 644.0, letter_e.color);
			render_english_da(letter_r.vertices, letter_r.vnumber, width, height, 673.0, letter_r.color);
			render_english_da(letter_s.vertices, letter_s.vnumber, width, height, 692.0, letter_s.color);
			render_english_da(letter_i.vertices, letter_i.vnumber, width, height, 718.0, letter_i.color);
			render_english_da(letter_t.vertices, letter_t.vnumber, width, height, 730.0, letter_t.color);
			render_english_da(letter_y.vertices, letter_y.vnumber, width, height, 747.0, letter_y.color);
			break;
		case MY_DRAW_ELEMENTS:
			/*National*/
			render_english_de(letter_N.vertices, letter_N.vnumber, width, height, 25.0, letter_N.color);
			render_english_de(letter_a.vertices, letter_a.vnumber, width, height, 57.0, letter_a.color);
			render_english_de(letter_t.vertices, letter_t.vnumber, width, height, 86.0, letter_t.color);
			render_english_de(letter_i.vertices, letter_i.vnumber, width, height, 104.0, letter_i.color);
			render_english_de(letter_o.vertices, letter_o.vnumber, width, height, 115.0, letter_o.color);
			render_english_de(letter_n.vertices, letter_n.vnumber, width, height, 145.0, letter_n.color);
			render_english_de(letter_a.vertices, letter_a.vnumber, width, height, 174.0, letter_a.color);
			render_english_de(letter_l.vertices, letter_l.vnumber, width, height, 204.0, letter_l.color);

			/*Chung*/
			render_english_de(letter_C.vertices, letter_C.vnumber, width, height, 228.0, letter_C.color);
			render_english_de(letter_h.vertices, letter_h.vnumber, width, height, 265.0, letter_h.color);
			render_english_de(letter_u.vertices, letter_u.vnumber, width, height, 293.0, letter_u.color);
			render_english_de(letter_n.vertices, letter_n.vnumber, width, height, 323.0, letter_n.color);
			render_english_de(letter_g.vertices, letter_g.vnumber, width, height, 351.0, letter_g.color);

			/*Hsing*/
			render_english_de(letter_H.vertices, letter_H.vnumber, width, height, 393.0, letter_H.color);
			render_english_de(letter_s.vertices, letter_s.vnumber, width, height, 428.0, letter_s.color);
			render_english_de(letter_i.vertices, letter_i.vnumber, width, height, 456.0, letter_i.color);
			render_english_de(letter_n.vertices, letter_n.vnumber, width, height, 468.0, letter_n.color);
			render_english_de(letter_g.vertices, letter_g.vnumber, width, height, 497.0, letter_g.color);

			/*University*/
			render_english_de(letter_U.vertices, letter_U.vnumber, width, height, 539.0, letter_U.color);
			render_english_de(letter_n.vertices, letter_n.vnumber, width, height, 574.0, letter_n.color);
			render_english_de(letter_i.vertices, letter_i.vnumber, width, height, 604.0, letter_i.color);
			render_english_de(letter_v.vertices, letter_v.vnumber, width, height, 616.0, letter_v.color);
			render_english_de(letter_e.vertices, letter_e.vnumber, width, height, 644.0, letter_e.color);
			render_english_de(letter_r.vertices, letter_r.vnumber, width, height, 673.0, letter_r.color);
			render_english_de(letter_s.vertices, letter_s.vnumber, width, height, 692.0, letter_s.color);
			render_english_de(letter_i.vertices, letter_i.vnumber, width, height, 718.0, letter_i.color);
			render_english_de(letter_t.vertices, letter_t.vnumber, width, height, 730.0, letter_t.color);
			render_english_de(letter_y.vertices, letter_y.vnumber, width, height, 747.0, letter_y.color);
			break;
		case MY_MULTI_DRAW_ARRAYS:
			/*National*/
			render_english_mda(letter_N.vertices, letter_N.vnumber, width, height, 25.0, letter_N.color);
			render_english_mda(letter_a.vertices, letter_a.vnumber, width, height, 57.0, letter_a.color);
			render_english_mda(letter_t.vertices, letter_t.vnumber, width, height, 86.0, letter_t.color);
			render_english_mda(letter_i.vertices, letter_i.vnumber, width, height, 104.0, letter_i.color);
			render_english_mda(letter_o.vertices, letter_o.vnumber, width, height, 115.0, letter_o.color);
			render_english_mda(letter_n.vertices, letter_n.vnumber, width, height, 145.0, letter_n.color);
			render_english_mda(letter_a.vertices, letter_a.vnumber, width, height, 174.0, letter_a.color);
			render_english_mda(letter_l.vertices, letter_l.vnumber, width, height, 204.0, letter_l.color);

			/*Chung*/
			render_english_mda(letter_C.vertices, letter_C.vnumber, width, height, 228.0, letter_C.color);
			render_english_mda(letter_h.vertices, letter_h.vnumber, width, height, 265.0, letter_h.color);
			render_english_mda(letter_u.vertices, letter_u.vnumber, width, height, 293.0, letter_u.color);
			render_english_mda(letter_n.vertices, letter_n.vnumber, width, height, 323.0, letter_n.color);
			render_english_mda(letter_g.vertices, letter_g.vnumber, width, height, 351.0, letter_g.color);

			/*Hsing*/
			render_english_mda(letter_H.vertices, letter_H.vnumber, width, height, 393.0, letter_H.color);
			render_english_mda(letter_s.vertices, letter_s.vnumber, width, height, 428.0, letter_s.color);
			render_english_mda(letter_i.vertices, letter_i.vnumber, width, height, 456.0, letter_i.color);
			render_english_mda(letter_n.vertices, letter_n.vnumber, width, height, 468.0, letter_n.color);
			render_english_mda(letter_g.vertices, letter_g.vnumber, width, height, 497.0, letter_g.color);

			/*University*/
			render_english_mda(letter_U.vertices, letter_U.vnumber, width, height, 539.0, letter_U.color);
			render_english_mda(letter_n.vertices, letter_n.vnumber, width, height, 574.0, letter_n.color);
			render_english_mda(letter_i.vertices, letter_i.vnumber, width, height, 604.0, letter_i.color);
			render_english_mda(letter_v.vertices, letter_v.vnumber, width, height, 616.0, letter_v.color);
			render_english_mda(letter_e.vertices, letter_e.vnumber, width, height, 644.0, letter_e.color);
			render_english_mda(letter_r.vertices, letter_r.vnumber, width, height, 673.0, letter_r.color);
			render_english_mda(letter_s.vertices, letter_s.vnumber, width, height, 692.0, letter_s.color);
			render_english_mda(letter_i.vertices, letter_i.vnumber, width, height, 718.0, letter_i.color);
			render_english_mda(letter_t.vertices, letter_t.vnumber, width, height, 730.0, letter_t.color);
			render_english_mda(letter_y.vertices, letter_y.vnumber, width, height, 747.0, letter_y.color);
			break;
		case MY_MULTI_DRAW_ELEMENTS:
			/*National*/
			render_english_mde(letter_N.vertices, letter_N.vnumber, width, height, 25.0, letter_N.color);
			render_english_mde(letter_a.vertices, letter_a.vnumber, width, height, 57.0, letter_a.color);
			render_english_mde(letter_t.vertices, letter_t.vnumber, width, height, 86.0, letter_t.color);
			render_english_mde(letter_i.vertices, letter_i.vnumber, width, height, 104.0, letter_i.color);
			render_english_mde(letter_o.vertices, letter_o.vnumber, width, height, 115.0, letter_o.color);
			render_english_mde(letter_n.vertices, letter_n.vnumber, width, height, 145.0, letter_n.color);
			render_english_mde(letter_a.vertices, letter_a.vnumber, width, height, 174.0, letter_a.color);
			render_english_mde(letter_l.vertices, letter_l.vnumber, width, height, 204.0, letter_l.color);

			/*Chung*/
			render_english_mde(letter_C.vertices, letter_C.vnumber, width, height, 228.0, letter_C.color);
			render_english_mde(letter_h.vertices, letter_h.vnumber, width, height, 265.0, letter_h.color);
			render_english_mde(letter_u.vertices, letter_u.vnumber, width, height, 293.0, letter_u.color);
			render_english_mde(letter_n.vertices, letter_n.vnumber, width, height, 323.0, letter_n.color);
			render_english_mde(letter_g.vertices, letter_g.vnumber, width, height, 351.0, letter_g.color);

			/*Hsing*/
			render_english_mde(letter_H.vertices, letter_H.vnumber, width, height, 393.0, letter_H.color);
			render_english_mde(letter_s.vertices, letter_s.vnumber, width, height, 428.0, letter_s.color);
			render_english_mde(letter_i.vertices, letter_i.vnumber, width, height, 456.0, letter_i.color);
			render_english_mde(letter_n.vertices, letter_n.vnumber, width, height, 468.0, letter_n.color);
			render_english_mde(letter_g.vertices, letter_g.vnumber, width, height, 497.0, letter_g.color);

			/*University*/
			render_english_mde(letter_U.vertices, letter_U.vnumber, width, height, 539.0, letter_U.color);
			render_english_mde(letter_n.vertices, letter_n.vnumber, width, height, 574.0, letter_n.color);
			render_english_mde(letter_i.vertices, letter_i.vnumber, width, height, 604.0, letter_i.color);
			render_english_mde(letter_v.vertices, letter_v.vnumber, width, height, 616.0, letter_v.color);
			render_english_mde(letter_e.vertices, letter_e.vnumber, width, height, 644.0, letter_e.color);
			render_english_mde(letter_r.vertices, letter_r.vnumber, width, height, 673.0, letter_r.color);
			render_english_mde(letter_s.vertices, letter_s.vnumber, width, height, 692.0, letter_s.color);
			render_english_mde(letter_i.vertices, letter_i.vnumber, width, height, 718.0, letter_i.color);
			render_english_mde(letter_t.vertices, letter_t.vnumber, width, height, 730.0, letter_t.color);
			render_english_mde(letter_y.vertices, letter_y.vnumber, width, height, 747.0, letter_y.color);
			break;
		default:
			break;
	}
	
}